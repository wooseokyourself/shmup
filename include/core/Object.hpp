#ifndef __OBJECT__
#define __OBJECT__

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>

#include <core/assimp/cimport.h>
#include <core/assimp/Importer.hpp>
#include <core/assimp/scene.h>
#include <core/assimp/postprocess.h>

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
    virtual void display(const glm::mat4& viewProjectionMat, const glm::mat4& parentModelViewMat) {
        const glm::mat4 ctm = parentModelViewMat * this->modelViewMat.get();
        if (shader[NONLIGHT] && drawFlag) {
            shader[NONLIGHT]->bind();

            // vertex shader uniforms
            shader[NONLIGHT]->setUniformMat4("mvp", viewProjectionMat * ctm);

            // fragment shader uniforms
            shader[NONLIGHT]->setUniformVec4("color", color);

            for (Mesh mesh : meshes)
                mesh.draw();
            shader[NONLIGHT]->unbind();
        }
        for (Object* child : children)
            child->display(viewProjectionMat, ctm);
    }
    virtual void display(const glm::mat4& viewProjectionMat, const glm::mat4& parentModelViewMat,
                        const DirectionalLightFactors& dFactors, const std::vector<PointLightFactors>& pFactors, const glm::vec3& viewPos) {
        const glm::mat4 ctm = parentModelViewMat * this->modelViewMat.get();
        if (shader[PHONG] && drawFlag) {
            shader[PHONG]->bind();

            // vertex shader uniforms
            shader[PHONG]->setUniformMat4("mvp", viewProjectionMat * ctm);
            shader[PHONG]->setUniformMat4("modelViewMat", this->modelViewMat.get());
            shader[PHONG]->setUniformMat3("modelViewMatForNormal", glm::mat3(glm::transpose(glm::inverse(this->modelViewMat.get()))));

            // fragment shader uniforms
            // Directional Light
            shader[PHONG]->setUniformVec4("dFactors.color", dFactors.color);
            shader[PHONG]->setUniformVec3("dFactors.lightDirection", dFactors.lightDirection);
            shader[PHONG]->setUniformFloat("dFactors.ambientStrength", dFactors.ambientStrength);
            shader[PHONG]->setUniformFloat("dFactors.specularStrength", dFactors.specularStrength);
            shader[PHONG]->setUniformFloat("dFactors.shininess", dFactors.shininess);

            // Point Light
            for (int i = 0; i < pFactors.size(); i++) {
                shader[PHONG]->setUniformVec4("pFactors[" + std::to_string(i) + "].color", pFactors[i].color);
                shader[PHONG]->setUniformVec3("pFactors[" + std::to_string(i) + "].lightPosition", pFactors[i].lightPosition);
                shader[PHONG]->setUniformFloat("pFactors[" + std::to_string(i) + "].ambientStrength", pFactors[i].ambientStrength);
                shader[PHONG]->setUniformFloat("pFactors[" + std::to_string(i) + "].specularStrength", pFactors[i].specularStrength);
                shader[PHONG]->setUniformFloat("pFactors[" + std::to_string(i) + "].shininess", pFactors[i].shininess);
                shader[PHONG]->setUniformFloat("pFactors[" + std::to_string(i) + "].constant", pFactors[i].constant);
                shader[PHONG]->setUniformFloat("pFactors[" + std::to_string(i) + "].linear", pFactors[i].linear);
                shader[PHONG]->setUniformFloat("pFactors[" + std::to_string(i) + "].quadratic", pFactors[i].quadratic);
            }

            shader[PHONG]->setUniformVec4("objColor", color);
            shader[PHONG]->setUniformInt("pointLightNumber", pFactors.size());
            shader[PHONG]->setUniformVec3("viewPos", viewPos);

            // shader[PHONG]->setUniformFloat("ambientStrength", 0.01f);
            // shader[PHONG]->setUniformFloat("specularStrength", 0.5f);
            // shader[PHONG]->setUniformFloat("shininess", 32.0f);

            for (Mesh mesh : meshes)
                mesh.draw();
            shader[PHONG]->unbind();
        }
        for (Object* child : children)
            child->display(viewProjectionMat, ctm, dFactors, pFactors, viewPos);
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
    void pushMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
        meshes.push_back(Mesh(vertices, indices));
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
        for (int i = 0 ; i < node->mNumMeshes ; i ++) { 
            const aiMesh* mesh = scene->mMeshes[meshIdx[i]];
            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;
            for (int j = 0 ; j < mesh->mNumVertices ; j ++) { // Vertices
                Vertex v;
                v.pos = glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);
                if (mesh->HasNormals())
                    v.norm = glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);
                vertices.push_back(v);
            }
            for (int j = 0 ; j < mesh->mNumFaces ; j ++) {
                if (mesh->mFaces->mNumIndices == 3) {
                    indices.push_back(mesh->mFaces[j].mIndices[0]);
                    indices.push_back(mesh->mFaces[j].mIndices[1]);
                    indices.push_back(mesh->mFaces[j].mIndices[2]);
                }
                else {
                    std::cout << "WARNING::ASSIMP::NON_TRIANGLE_FACE: " << mesh->mFaces->mNumIndices << std::endl;
                }
            }
            meshes.push_back(Mesh(vertices, indices));
        }
        for (int i = 0 ; i < node->mNumChildren ; i ++)
            assimpToMesh(node->mChildren[i], scene);
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