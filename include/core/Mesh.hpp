#ifndef __MESH__
#define __MESH__

#include <string>

#include <core/GL/glew.h>
#include <core/GL/freeglut.h>
#include <core/glm/glm.hpp>
#include <core/glm/gtc/type_ptr.hpp>
#include <core/glm/gtx/string_cast.hpp>

#include <core/assimp/cimport.h>
#include <core/assimp/Importer.hpp>
#include <core/assimp/scene.h>
#include <core/assimp/postprocess.h>

#include "core/Utility.hpp"

#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b

class Mesh {
public:
    Mesh () : wireframe(true) {
        color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    void draw () const {
        if (scene == nullptr)
            return;
        glEnable(GL_LIGHTING);
        if (wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            drawBoundingBox();
        }
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glColor4f(color.r, color.g, color.b, color.a);
        drawMeshes(scene->mRootNode);
    }
    bool loadModel (std::string path) {
        scene = aiImportFile(path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
        if (scene) {
            calculateBoundingBox();
            width = abs(bbMin.x - bbMax.x);
            height = abs(bbMin.y - bbMax.y);
            depth = abs(bbMin.z - bbMax.z);
            longestSide = max(width, height);
            longestSide = max(longestSide, depth);

            bbVertices.clear();
            bbVertices.push_back(glm::vec3(bbMin.x, bbMin.y, bbMax.z));
            bbVertices.push_back(glm::vec3(bbMax.x, bbMin.y, bbMax.z));
            bbVertices.push_back(glm::vec3(bbMax.x, bbMax.y, bbMax.z));
            bbVertices.push_back(glm::vec3(bbMin.x, bbMax.y, bbMax.z));
            bbVertices.push_back(glm::vec3(bbMin.x, bbMin.y, bbMin.z));
            bbVertices.push_back(glm::vec3(bbMax.x, bbMin.y, bbMin.z));
            bbVertices.push_back(glm::vec3(bbMax.x, bbMax.y, bbMin.z));
            bbVertices.push_back(glm::vec3(bbMin.x, bbMax.y, bbMin.z));
            
            return true;
        }
        return false;
    }

public:
    void setColor (const float r, const float g, const float b, const float a) {
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }
    void setColor (const glm::vec4 _color) {
        color = _color;
    }
    void setRandomColor () {
        color = glm::vec4(randomRealNumber(0.0f, 1.0f), randomRealNumber(0.0f, 1.0f), randomRealNumber(0.0f, 1.0f), 1.0f);
    }
    glm::vec4 getColor () const {
        return color;
    }
    float getLongestSide () const {
        return longestSide;
    }
    void setWireframe (bool flag) {
        wireframe = flag;
    }
    glm::vec3 getBoundingBoxMin () const {
        return bbMin;
    }
    glm::vec3 getBoundingBoxMax () const {
        return bbMax;
    }

private:
    void drawMeshes (const aiNode* node) const {
        for (int i = 0 ; i < node->mNumMeshes; i ++) {
            const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            for (int j = 0 ; j < mesh->mNumFaces ; j ++) {
                const aiFace* face = &mesh->mFaces[j];
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
                for(int k = 0 ; k < face->mNumIndices ; k ++) {
                    int idx = face->mIndices[k];
                    if(mesh->mNormals != NULL)
                        glNormal3fv(&mesh->mNormals[idx].x);
                    glVertex3fv(&mesh->mVertices[idx].x);
                }
                glEnd();
            }
        }
        for (int i = 0 ; i < node->mNumChildren ; i ++)
            drawMeshes(node->mChildren[i]);
    }
    void drawBoundingBox () const {
        if (bbVertices.size() != 8)
            return;
        glDisable(GL_LIGHTING);
        std::vector<int> indices = {0, 1, 1, 2, 2, 3, 3, 0,
                                    4, 5, 5, 6, 6, 7, 7, 4,
                                    0, 4, 1, 5, 2, 6, 3, 7};
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(1.0f, 0.0f, 1.0f);
        glBegin(GL_LINE_STRIP);
        for (int i = 0 ; i < indices.size() ; i ++)
            glVertex3f(bbVertices[indices[i]].x, bbVertices[indices[i]].y, bbVertices[indices[i]].z);
        glEnd();

        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_LINE_LOOP);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(10.0f, 0.0f, 0.0f);
        glEnd();

        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_LINE_LOOP);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 10.0f, 0.0f);
        glEnd();

        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 10.0f);
        glEnd();
    }
    void calculateBoundingBox () {
        aiMatrix4x4 mat;
        aiIdentityMatrix4(&mat);
        bbMin.x = bbMin.y = bbMin.z = 1e10f;
        bbMax.x = bbMax.y = bbMax.z = -1e10f;
        calculateBoundingBoxForNode(scene->mRootNode, &mat);
    }
    void calculateBoundingBoxForNode (const aiNode* node, aiMatrix4x4* mat) {
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
            calculateBoundingBoxForNode(node->mChildren[i], mat);
        *mat = prevMat;
    }

private:
    const aiScene* scene;
    glm::vec4 color;
    bool wireframe;
    glm::vec3 bbMin;
    glm::vec3 bbMax;
    std::vector<glm::vec3> bbVertices;
    float width;
    float height;
    float depth;
    float longestSide; // one of width, height, and depth
};

#endif