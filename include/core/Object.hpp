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

#include "core/Mesh.hpp"

class Object {
public:
    Object () : parent(nullptr), speed(0.0f), drawFlag(false) {
        translatef = glm::vec3(0.0f, 0.0f, 0.0f);
        scalef = glm::vec3(1.0f, 1.0f, 1.0f);
        inheritedScalef = 1.0f;
        modelViewMat = glm::mat4(1.0f);
    }
    virtual void update () {
        modelViewMat = glm::translate(glm::mat4(1.0f), translatef);
        for (int i = rotateAxisStack.size() - 1 ; i >= 0 ; i --)
            modelViewMat = glm::rotate(modelViewMat, getRadian(angleStack[i]), rotateAxisStack[i]);
        modelViewMat = glm::scale(modelViewMat, scalef); 
        for (Object* child : children) {
            child->inheritedScalef = inheritedScalef * scalef;
            child->update();
        }
    }
    virtual void display () {
        // 여기에서 쉐이더를 통한... 그리기..
    }

public:
    void loadModel (const std::string& path) {
        const aiScene* scene = aiImportFile(path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
        if (scene) {
            assimpToMesh(scene->mRootNode, scene);
            std::vector<glm::vec3> bb = getBoundingBox(scene);
        }
        else {
            std::cout << "ERROR::OBJECT::READ_MODEL_FAILED" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

public: // Scene graph
    Object* pushChild (Object* child) {
        child->parent = this;
        children.push_back(child);
        return child;
    }
    std::list<Object*>& getChildren () {
        return children;
    }
    Object* getParent () {
        return parent;
    }

public: // Transformations
    void translate (const glm::vec3 factors) {
        translatef += factors / inheritedScalef;
    }
    void setTranslate (const glm::vec3 factors} {
        translatef = factors / inheritedScalef;
    }
    void rotate (const float angle, const glm::vec3 axis) {
        if (angle != 0.0f) {
            rotateAxisStack.push_back(axis);
            angleStack.push_back(angle);
        }
    }
    void setRotate (const float angle, const glm::vec3 axis) {
        rotateAxisStack.clear();
        angleStack.clear();
        if (angle != 0.0f) {
            rotateAxisStack.push_back(axis);
            angleStack.push_back(angle);
        }
    }
    void setRotateStack (const std::vector<float> _angleStack, const std::vector<glm::vec3> _rotateAxisStack) {
        angleStack = _angleStack;
        rotateAxisStack = _rotateAxisStack;
    }
    void scale (const glm::vec3 factors) {
        scalef += factors;
    }
    void setLongestSideTo (const float len) {
        scalef.x = scalef.y = scalef.z = (len / longestSide) / inheritedScalef;
        update();
    }

public: // Utilities
    void setDraw (bool flag) {
        drawFlag = flag;
        for (Object* child : children)
            child->setDraw(flag);
    }
    glm::mat4 getModelViewMat () const {
        return modelViewMat;
    }
    glm::vec3 getUpVec () const {
        return modelViewMat[1]; // second column
    }
    glm::vec3 getFrontVec () const {
        return modelViewMat[2]; // third column
    }
    glm::vec3 getWorldPos () const {
        return translatef;
    }
    void setWireframe (bool flag) {
        // 쉐이더로 변경됨으로써 이 부분도 바뀌어야 한다.
        /*
        mesh.setWireframe (flag);
        for (Object* child : children)
            child->setWireframe(flag);
        */
    }
    void setSpeed (const float _speed) {
        speed = _speed;
    }
    float getSpeed () const {
        return speed;
    }
    void move (const glm::vec3 directionInModelFrame) {
        glm::vec4 unit = modelViewMat * glm::vec4(directionInModelFrame, 0);
        translate(glm::vec3(unit / glm::length(glm::vec3(unit)) * speed));
    }
    bool isIn (const glm::vec3 p) const {
        glm::vec3 worldVecA = glm::vec3(modelViewMat * glm::vec4(mesh.getBoundingBoxMin(), 1));
        glm::vec3 worldVecB = glm::vec3(modelViewMat * glm::vec4(mesh.getBoundingBoxMax(), 1));
    
        /*
        std::cout << "p: " << glm::to_string(p) << std::endl;
        std::cout << "a: " << glm::to_string(worldVecA) << std::endl;
        std::cout << "b: " << glm::to_string(worldVecB) << std::endl;
        */
       
        return (
                (worldVecA.x <= p.x && worldVecA.z <= p.z && worldVecB.x >= p.x && worldVecB.z >= p.z) ||
                (worldVecA.x >= p.x && worldVecA.z >= p.z && worldVecB.x <= p.x && worldVecB.z <= p.z)
            ) && (
                (worldVecA.y <= p.y && worldVecB.y >= p.y) || (worldVecA.y >= p.y && worldVecB.y <= p.y)
            );
    }
    bool isCenterOutOfWorld (const float axisLimitAbs) {
        glm::vec3 p = getWorldPos();
        return (
            p.x < -axisLimitAbs || p.x > axisLimitAbs ||
            p.y < -axisLimitAbs || p.y > axisLimitAbs ||
            p.z < -axisLimitAbs || p.z > axisLimitAbs
        ); 
    }

private:
    void assimpToMesh (aiNode* node, aiScene* scene) {
        for (int i = 0 ; i < node->mNumMeshes ; i ++) { // Mesh iteration, size: aiNode::mNumMeshes
            const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            for (int j = 0 ; j < mesh->mNumFaces ; j ++) { // Face iteration, size: aiMesh::mNumFaces
                const aiFace* face = &mesh->mFaces[j];
                /* // 여기서 drawing mode 는 어디에 저장?
                switch(face->mNumIndices) {
                    case 1: 
                        glBegin(GL_POINTS);
                        break;
                    case 2: 
                        glBegin(GL_LINES);
                        break;
                    case 3: 
                        glBegin(GL_TRIANGLES);
                        break;
                    default: 
                        glBegin(GL_POLYGON);
                        break;
                }
                */
                for(int k = 0 ; k < face->mNumIndices ; k ++) { // Vertices iteration, size: aiFace::mNumIndices
                    int idx = face->mIndices[k];
                    if(mesh->mNormals != NULL)
                    const aiVector3D& pos = mesh->mVertices[idx];
                    const aiVector3D& norm = mesh->mNormals[idx];
                    const glm::vec3 position = (pos.x, pos.y, pos.z);
                    const glm::vec3 normal = (norm.x, norm.y, norm.z);
                    this->mesh.pushBackVertex(vertex(position, normal));
                }
                glEnd();
            }
        }
        for (int i = 0 ; i < node->mNumChildren ; i ++)
            drawMeshes(node->mChildren[i]);
    }
    void getBoundingBox (const aiScene* scene) {
        aiMatrix4x4 mat;
        glm::vec3 bbMin, bbMax;
        std::vector<glm::vec3> bbVertices;
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
        bbVertices.push_back(glm::vec3(bbMin.x, bbMin.y, bbMax.z));
        bbVertices.push_back(glm::vec3(bbMax.x, bbMin.y, bbMax.z));
        bbVertices.push_back(glm::vec3(bbMax.x, bbMax.y, bbMax.z));
        bbVertices.push_back(glm::vec3(bbMin.x, bbMax.y, bbMax.z));
        bbVertices.push_back(glm::vec3(bbMin.x, bbMin.y, bbMin.z));
        bbVertices.push_back(glm::vec3(bbMax.x, bbMin.y, bbMin.z));
        bbVertices.push_back(glm::vec3(bbMax.x, bbMax.y, bbMin.z));
        bbVertices.push_back(glm::vec3(bbMin.x, bbMax.y, bbMin.z));

        return bbVertices;
    }
    void calculateBoundingBoxForNode (const aiScene* scene, const aiNode* node, aiMatrix4x4* mat, glm::vec3& bbMin, glm::vec3& bbMax) {
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

private: // Scene graph
    Object* parent;
    std::list<Object*> children;

private: // Mesh
    Mesh mesh;
    float longestSide;

private: // Model-view matrix
    glm::mat4x4 modelViewMat;
    glm::vec3 translatef;
    glm::vec3 scalef;
    float inheritedScalef;
    std::vector<glm::vec3> rotateAxisStack;
    std::vector<float> angleStack;

private: // Other properties
    bool drawFlag;
    float speed;
};

#endif