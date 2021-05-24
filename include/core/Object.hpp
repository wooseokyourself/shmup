#ifndef __OBJECT__
#define __OBJECT__

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <list>

#include <core/assimp/cimport.h>
#include <core/assimp/Importer.hpp>
#include <core/assimp/scene.h>
#include <core/assimp/postprocess.h>

#include <core/stb/stb_image.h>

#include "core/Utility.hpp"
#include "core/Mesh.hpp"
#include "core/Light.hpp"

using namespace std;

enum shaderType {
    NONLIGHT,
    PHONG,
    GOURAUD
};

class Object {
public:
    Object() : parent(nullptr), speed(0.0f), drawFlag(false) {
        shader = std::vector<Shader*>(3, nullptr);
        inheritedScalef = glm::vec3(1.0f, 1.0f, 1.0f);
        bbMax = glm::vec3(0.0f);
        bbMin = glm::vec3(0.0f);
        color = glm::vec4(1.0f);
        longestSide = 0.0f;
    }
    ~Object() {
        for (int i = 0; i < shader.size(); i++)
            delete shader[i];
    }
    virtual void update() {
        for (Object* child : children) {
            child->inheritedScalef = inheritedScalef * modelViewMat.getScale();
            child->update();
        }
    }

    virtual void display(const int shadingType, const glm::mat4& viewProjectionMat, const glm::mat4& parentModelViewMat,
                        const DirectionalLightFactors* dFactors, const std::vector<PointLightFactors*>& pFactorsArr, const glm::vec3& viewPos) {
        const glm::mat4 ctm = parentModelViewMat * this->modelViewMat.get();
        if (drawFlag) {
            if (!shader[shadingType]) {
                std::cout << "ERROR::OBJECT::TARGET_SHADER_NOT_LOADED: " << shadingType << std::endl;
            }
            else {
                shader[shadingType]->bind();

                switch (shadingType) {

                case PHONG: case GOURAUD: {
                    shader[shadingType]->setUniformMat4("mvp", viewProjectionMat * ctm);
                    shader[shadingType]->setUniformMat4("modelViewMat", this->modelViewMat.get());
                    shader[shadingType]->setUniformMat3("modelViewMatForNormal", glm::mat3(glm::transpose(glm::inverse(this->modelViewMat.get()))));

                    // Directional Light
                    shader[shadingType]->setUniformVec4("dFactors.color", dFactors->color);
                    shader[shadingType]->setUniformVec3("dFactors.lightDirection", dFactors->lightDirection);
                    shader[shadingType]->setUniformFloat("dFactors.ambientStrength", dFactors->ambientStrength);
                    shader[shadingType]->setUniformFloat("dFactors.specularStrength", dFactors->specularStrength);
                    shader[shadingType]->setUniformFloat("dFactors.shininess", dFactors->shininess);

                    // Point Light
                    for (int i = 0; i < pFactorsArr.size(); i++) {
                        shader[shadingType]->setUniformVec4("pFactors[" + std::to_string(i) + "].color", pFactorsArr[i]->color);
                        shader[shadingType]->setUniformVec3("pFactors[" + std::to_string(i) + "].lightPosition", pFactorsArr[i]->lightPosition);
                        shader[shadingType]->setUniformFloat("pFactors[" + std::to_string(i) + "].ambientStrength", pFactorsArr[i]->ambientStrength);
                        shader[shadingType]->setUniformFloat("pFactors[" + std::to_string(i) + "].specularStrength", pFactorsArr[i]->specularStrength);
                        shader[shadingType]->setUniformFloat("pFactors[" + std::to_string(i) + "].shininess", pFactorsArr[i]->shininess);
                        shader[shadingType]->setUniformFloat("pFactors[" + std::to_string(i) + "].constant", pFactorsArr[i]->constant);
                        shader[shadingType]->setUniformFloat("pFactors[" + std::to_string(i) + "].linear", pFactorsArr[i]->linear);
                        shader[shadingType]->setUniformFloat("pFactors[" + std::to_string(i) + "].quadratic", pFactorsArr[i]->quadratic);
                    }

                    shader[shadingType]->setUniformVec4("objColor", color);
                    shader[shadingType]->setUniformInt("pointLightNumber", pFactorsArr.size());
                    shader[shadingType]->setUniformVec3("viewPos", viewPos);
                    break;
                }

                case NONLIGHT: default: {
                    if (shadingType != NONLIGHT)
                        std::cout << "ERROR::OBJECT::INVALID_SHADER_TYPE: " << shadingType << std::endl;
                    shader[NONLIGHT]->setUniformMat4("mvp", viewProjectionMat * ctm);
                    shader[NONLIGHT]->setUniformVec4("color", color);
                    break;
                }

                }
                for (Mesh mesh : meshes)
                    mesh.draw(shader[shadingType]);
                shader[shadingType]->unbind();
            }
        }

        for (Object* child : children)
            child->display(shadingType, viewProjectionMat, ctm, dFactors, pFactorsArr, viewPos);
    }

public: // Scene graph
    Object* pushChild(Object* child) {
        child->parent = this;
        children.push_back(child);
        return child;
    }
    std::list<Object*>& getChildren() {
        return children;
    }
    Object* getParent() {
        return parent;
    }

public: // Transformations
    void translate(const glm::vec3 factors) {
        modelViewMat.translate(factors / inheritedScalef);
    }
    void setTranslate(const glm::vec3 factors) {
        modelViewMat.setTranslate(factors / inheritedScalef);
    }
    void rotate(const float angle, const glm::vec3 axis) {
        modelViewMat.rotate(angle, axis);
    }
    void setRotate(const float angle, const glm::vec3 axis) {
        modelViewMat.setRotate(angle, axis);
    }
    void setRotateStack(const std::vector<float> _angleStack, const std::vector<glm::vec3> _rotateAxisStack) {
        modelViewMat.setRotateStack(_angleStack, _rotateAxisStack);
    }
    void setScale(const glm::vec3 factors) {
        modelViewMat.setScale(factors);
    }
    void setLongestSideTo(const float len) {
        modelViewMat.setScale((len / longestSide) / inheritedScalef);
        update();
    }
    std::vector<float> getAngleStack() const {
        return modelViewMat.getAngleStack();
    }
    std::vector<glm::vec3> getRotateAxisStack() const {
        return modelViewMat.getRotateAxisStack();
    }
    glm::vec3 getScale() {
        return modelViewMat.getScale();
    }

public: // Utilities
    virtual void loadShader(unsigned int type, const std::string& vertPath, const std::string& fragPath) {
        if (shader[type])
            delete shader[type];
        shader[type] = new Shader(vertPath, fragPath);
    }
    virtual void setShader(unsigned int type, Shader* loadedShader) {
        shader[type] = loadedShader;
    }
void loadModel(const std::string& path) {
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return;
    }
    assimpToMesh(scene->mRootNode, scene);
    calcBoundingBox(scene);
}
    void pushMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const int texture) {
        meshes.push_back(Mesh(vertices, indices, texture));
    }
    virtual void setDraw(bool flag) {
        drawFlag = flag;
        for (Object* child : children)
            child->setDraw(flag);
    }
    ModelViewMat cloneModelViewObj() const {
        return modelViewMat;
    }
    void setModelViewMat(const ModelViewMat& _mat) {
        modelViewMat = _mat;
    }
    glm::mat4 getModelViewMat() {
        return modelViewMat.get();
    }
    glm::vec3 getUpVec() {
        return modelViewMat.get()[1]; // second column
    }
    glm::vec3 getFrontVec() {
        return modelViewMat.get()[2]; // third column
    }
    glm::vec3 getTranslateVec() {
        return modelViewMat.get()[3];
    }
    glm::vec3 getWorldPos() { // return root.mat * ... * curr.mat * pos
        Object* par = parent;
        std::stack<glm::mat4> parentMatStack;
        glm::mat4 ctm(1.0f);
        while (par != nullptr) {
            parentMatStack.push(par->getModelViewMat());
            par = par->parent;
        }
        while (!parentMatStack.empty()) {
            ctm *= parentMatStack.top();
            parentMatStack.pop();
        }
        ctm *= getModelViewMat();
        return ctm * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    void setSpeed(const float _speed) {
        speed = _speed;
    }
    float getSpeed() const {
        return speed;
    }
    void move(const glm::vec3 directionInModelFrame) {
        glm::vec4 unit = modelViewMat.get() * glm::vec4(directionInModelFrame, 0);
        translate(glm::vec3(unit / glm::length(glm::vec3(unit)) * speed));
    }
    bool isIn(const glm::vec3 p) {
        glm::vec3 worldVecA = glm::vec3(modelViewMat.get() * glm::vec4(bbMin, 1));
        glm::vec3 worldVecB = glm::vec3(modelViewMat.get() * glm::vec4(bbMax, 1));
        return (
                (worldVecA.x <= p.x && worldVecA.z <= p.z && worldVecB.x >= p.x && worldVecB.z >= p.z) ||
                (worldVecA.x >= p.x && worldVecA.z >= p.z && worldVecB.x <= p.x && worldVecB.z <= p.z)
            ) && (
                (worldVecA.y <= p.y && worldVecB.y >= p.y) || (worldVecA.y >= p.y && worldVecB.y <= p.y)
            );
    }
    bool isCenterOutOfWorld(const float axisLimitAbs) {
        glm::vec3 p = getTranslateVec();
        return (
            p.x < -axisLimitAbs || p.x > axisLimitAbs ||
            p.y < -axisLimitAbs || p.y > axisLimitAbs ||
            p.z < -axisLimitAbs || p.z > axisLimitAbs
        ); 
    }
    void setShaderLightingMode(const int lightingFlag) const {
        if (shader[PHONG]) {
            shader[PHONG]->bind();
            shader[PHONG]->setUniformInt("lightingFlag", lightingFlag);
            shader[PHONG]->unbind();
        }
        if (shader[GOURAUD]) {
            shader[GOURAUD]->bind();
            shader[GOURAUD]->setUniformInt("lightingFlag", lightingFlag);
            shader[GOURAUD]->unbind();
        }
        for (Object* child : children)
            child->setShaderLightingMode(lightingFlag);
    }

public: // Colors
    void setColor(const glm::vec4 _color) {
        color = _color;
    }
    void setRandomColor() {
        color = glm::vec4(randomRealNumber(0.0f, 1.0f), randomRealNumber(0.0f, 1.0f), randomRealNumber(0.0f, 1.0f), 1.0f);
    }
    glm::vec4 getColor() const {
        return color;
    }

private:
    void assimpToMesh(aiNode* node, const aiScene* scene) {
        /**
         * loadModel 에서 aiProcess_Triangulate 옵션으로 모델을 불러오기 떄문에 
         * 모든 primitive는 삼각형으로 재구성된다. 그러므로 glDrawArray에서 primitive 종류를
         * 신경써줄 필요가 없다. (모두 GL_TRIANGLES 로 통일)
         */
        const unsigned int* meshIdx = node->mMeshes;
        for (int i = 0; i < node->mNumMeshes; i ++) { 
            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;
            unsigned int texture;

            const aiMesh* mesh = scene->mMeshes[meshIdx[i]];
            for (int j = 0; j < mesh->mNumVertices; j ++) { // Vertices
                Vertex v;
                v.pos = glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);
                if (mesh->HasNormals())
                    v.norm = glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);
                vertices.push_back(v);
                if (mesh->mTextureCoords[0])
                    v.textureCoord = glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);
            }
            for (int j = 0; j < mesh->mNumFaces; j ++) {
                if (mesh->mFaces->mNumIndices == 3) {
                    indices.push_back(mesh->mFaces[j].mIndices[0]);
                    indices.push_back(mesh->mFaces[j].mIndices[1]);
                    indices.push_back(mesh->mFaces[j].mIndices[2]);
                }
                else {
                    std::cout << "WARNING::ASSIMP::NON_TRIANGLE_FACE: " << mesh->mFaces->mNumIndices << std::endl;
                }
            }
            const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            texture = processTextureDiffuse(material);

            meshes.push_back(Mesh(vertices, indices, texture));
        }
        for (int i = 0 ; i < node->mNumChildren ; i ++)
            assimpToMesh(node->mChildren[i], scene);
    }
    unsigned int processTextureDiffuse(const aiMaterial* material) {
        // if (material->GetTextureCount(aiTextureType_DIFFUSE) == 0)
        //     return;
        unsigned int texture;
        aiString filePath;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &filePath);
        glGenTextures(1, &texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        std::cout << "Texture.ID: " << texture << ", TextureCount: " << material->GetTextureCount(aiTextureType_DIFFUSE) <<  ", Diffuse Texture: " << filePath.C_Str() << std::endl;

        int w, h, ch;
        unsigned char* pixelData = stbi_load(filePath.C_Str(), &w, &h, &ch, 0);
        if (pixelData) {
            GLenum channel;
            switch (ch) {
                case 1: channel = GL_RED; break;
                case 3: channel = GL_RGB; break;
                case 4: channel = GL_RGBA; break;
            }
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, channel, w, h, 0, channel, GL_UNSIGNED_BYTE, pixelData);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "WARNING::TEXTURE::FAILED_TO_LOAD_AT_PATH: " << filePath.C_Str() << std::endl;
            texture = -1;
        }
        stbi_image_free(pixelData);
        
        return texture;
    }
    void calcBoundingBox(const aiScene* scene) {
        aiMatrix4x4 mat;
        aiIdentityMatrix4(&mat);
        bbMin.x = bbMin.y = bbMin.z = 1e10f;
        bbMax.x = bbMax.y = bbMax.z = -1e10f;
        calculateBoundingBoxForNode(scene, scene->mRootNode, &mat, bbMin, bbMax);

        // Calculate longest side
        float width = abs(bbMin.x - bbMax.x);
        float height = abs(bbMin.y - bbMax.y);
        float depth = abs(bbMin.z - bbMax.z);
        longestSide = max(width, height);
        longestSide = max(longestSide, depth);

        // Calculate vertices of bounding box
        /*
        bbVertices.push_back(glm::vec3(bbMin.x, bbMin.y, bbMax.z));
        bbVertices.push_back(glm::vec3(bbMax.x, bbMin.y, bbMax.z));
        bbVertices.push_back(glm::vec3(bbMax.x, bbMax.y, bbMax.z));
        bbVertices.push_back(glm::vec3(bbMin.x, bbMax.y, bbMax.z));
        bbVertices.push_back(glm::vec3(bbMin.x, bbMin.y, bbMin.z));
        bbVertices.push_back(glm::vec3(bbMax.x, bbMin.y, bbMin.z));
        bbVertices.push_back(glm::vec3(bbMax.x, bbMax.y, bbMin.z));
        bbVertices.push_back(glm::vec3(bbMin.x, bbMax.y, bbMin.z));
        */
    }
    void calculateBoundingBoxForNode(const aiScene* scene, const aiNode* node, aiMatrix4x4* mat, glm::vec3& bbMin, glm::vec3& bbMax) {
        aiMatrix4x4 prevMat = *mat;
        aiMultiplyMatrix4(mat, &node->mTransformation);
        for (int i = 0 ; i < node->mNumMeshes ; i ++) {
            const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            for (int j = 0 ; j < mesh->mNumVertices ; j ++) {
                aiVector3D tmp = mesh->mVertices[j];
                aiTransformVecByMatrix4(&tmp, mat);
                bbMin.x = min(bbMin.x, tmp.x);
                bbMin.y = min(bbMin.y, tmp.y);
                bbMin.z = min(bbMin.z, tmp.z);
                bbMax.x = max(bbMax.x, tmp.x);
                bbMax.y = max(bbMax.y, tmp.y);
                bbMax.z = max(bbMax.z, tmp.z);
            }
        }
        for (int i = 0 ; i < node->mNumChildren ; i ++)
            calculateBoundingBoxForNode(scene, node->mChildren[i], mat, bbMin, bbMax);
        *mat = prevMat;
    }

protected:
    std::vector<Shader*> shader;

protected: // Model-view matrix
    ModelViewMat modelViewMat;
    glm::vec3 inheritedScalef;

protected: // Mesh
    std::vector<Mesh> meshes;
    float longestSide;
    glm::vec3 bbMin;
    glm::vec3 bbMax;
    // std::vector<glm::vec3> bbVertices;

private: // Scene graph
    Object* parent;
    std::list<Object*> children;

private: // Other properties
    glm::vec4 color;
    bool drawFlag;
    float speed;
};

#endif