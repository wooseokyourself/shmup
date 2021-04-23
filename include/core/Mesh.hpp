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
    Mesh () : wireframe(false) {
        color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    void draw () {
        if (scene) {
            glColor4f(color.r, color.g, color.b, color.a);
            drawMeshes(scene, scene->mRootNode);

            if (wireframe && bbVertices.size() == 8) {
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
        }
    }
    bool loadModel (std::string path) {
        scene = aiImportFile(path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
        if (scene) {
            calculate_bounding_box();
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
    void drawMeshes (const aiScene* sc, const aiNode* nd) {
        unsigned int i;
        unsigned int n = 0, t;
        aiMatrix4x4 m = nd->mTransformation;

        /* update transform */
        aiTransposeMatrix4(&m);
        glPushMatrix();
        glMultMatrixf((float*)&m);

        /* draw all meshes assigned to this node */
        for (; n < nd->mNumMeshes; ++n) {
            const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

            apply_material(sc->mMaterials[mesh->mMaterialIndex]);

            if(mesh->mNormals == NULL) {
                glDisable(GL_LIGHTING);
            } else {
                glEnable(GL_LIGHTING);
            }

            for (t = 0; t < mesh->mNumFaces; ++t) {
                const aiFace* face = &mesh->mFaces[t];
                GLenum face_mode;

                switch(face->mNumIndices) {
                    case 1: face_mode = GL_POINTS; break;
                    case 2: face_mode = GL_LINES; break;
                    case 3: face_mode = GL_TRIANGLES; break;
                    default: face_mode = GL_POLYGON; break;
                }

                glBegin(face_mode);

                for(i = 0; i < face->mNumIndices; i++) {
                    int index = face->mIndices[i];
                    if(mesh->mColors[0] != NULL)
                        glColor4fv((GLfloat*)&mesh->mColors[0][index]);
                    if(mesh->mNormals != NULL)
                        glNormal3fv(&mesh->mNormals[index].x);
                    glVertex3fv(&mesh->mVertices[index].x);
                }

                glEnd();
            }

        }

        /* draw all children */
        for (n = 0; n < nd->mNumChildren; ++n) {
            drawMeshes(sc, nd->mChildren[n]);
        }

        glPopMatrix();
    }
    void apply_material (const aiMaterial *mtl) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)));
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f)));
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));

        unsigned int max = 1;
        float shininess, strength;
        int ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
        if (ret1 == AI_SUCCESS) {
            max = 1;
            int ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
            if (ret2 == AI_SUCCESS)
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
            else
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
        }
        else {
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)));
        }
        glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);

        max = 1;
        int two_sided;
        if ((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
            glDisable(GL_CULL_FACE);
        else
            glEnable(GL_CULL_FACE);
    }
    void calculate_bounding_box () {
        aiMatrix4x4 trafo;
        aiIdentityMatrix4(&trafo);
        bbMin.x = bbMin.y = bbMin.z = 1e10f;
        bbMax.x = bbMax.y = bbMax.z = -1e10f;
        calculate_bounding_box_for_node(scene->mRootNode, &trafo);
    }
    void calculate_bounding_box_for_node (const aiNode* nd, aiMatrix4x4* trafo ) {
        aiMatrix4x4 prev;
        unsigned int n = 0, t;

        prev = *trafo;
        aiMultiplyMatrix4(trafo,&nd->mTransformation);

        for (; n < nd->mNumMeshes; ++n) {
            const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
            for (t = 0; t < mesh->mNumVertices; ++t) {

                aiVector3D tmp = mesh->mVertices[t];
                aiTransformVecByMatrix4(&tmp,trafo);

                bbMin.x = min(bbMin.x,tmp.x);
                bbMin.y = min(bbMin.y,tmp.y);
                bbMin.z = min(bbMin.z,tmp.z);

                bbMax.x = max(bbMax.x,tmp.x);
                bbMax.y = max(bbMax.y,tmp.y);
                bbMax.z = max(bbMax.z,tmp.z);
            }
        }

        for (n = 0; n < nd->mNumChildren; ++n) {
            calculate_bounding_box_for_node(nd->mChildren[n], trafo);
        }
        *trafo = prev;
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