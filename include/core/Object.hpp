#ifndef __OBJECT__
#define __OBJECT__

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <core/GL/glew.h>
#include <core/GL/freeglut.h>
#include <core/glm/glm.hpp>
#include <core/glm/gtx/string_cast.hpp>

#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "core/Utility.hpp"

#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b

class Object {
public:
    Object () : parent(nullptr), speed(0.0f), anglef(0.0f) {
        color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        translatef = glm::vec3(0.0f, 0.0f, 0.0f);
        rotatef = glm::vec3(0.0f, 0.0f, 0.0f);
        scalef = glm::vec3(1.0f, 1.0f, 1.0f);
    }
    void loadModel (std::string path) {
        scene = aiImportFile(path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
        if (scene) {
            glm::vec3 _min, _max;
            calculate_bounding_box(&_min, &_max);
            width = abs(_min.x - _max.x);
            height = abs(_min.y - _max.y);
            depth = abs(_min.z - _max.z);
        }
        else
            std::cout << "model load failed" << std::endl;
    }
    virtual void update () {
        for (Object* child : children)
            child->update();
    }
    virtual void draw () {
        glPushMatrix();
        glTranslatef(translatef.x, translatef.y, translatef.z);
        glRotatef(anglef, rotatef.x, rotatef.y, rotatef.z);
        glScalef(scalef.x, scalef.y, scalef.z);
        if (scene) {
            glColor4f(color.r, color.g, color.b, color.a);
            drawMeshes(scene, scene->mRootNode);
        }
        for (Object* child : children)
            child->draw();
        glPopMatrix();
    }

public: // Scene graph
    Object* pushChild (Object* child) {
        child->parent = this;
        children.push_back(child);
        return child;
    }

public: // Model-view matrix
    void pasteModelViewMatrix (const Object& ref) {
        translatef = ref.translatef;
        rotatef = ref.rotatef;
        scalef = ref.scalef;
        anglef = ref.anglef;
    }   
    void translate (const float x, const float y, const float z) {
        translatef.x += x;
        translatef.y += y;
        translatef.z += z;
    }
    void translate (const glm::vec3 vec) {
        translatef.x += vec.x;
        translatef.y += vec.y;
        translatef.z += vec.z;
    }
    void rotate (const float angle) {
        anglef += angle;
    }
    void scale (const float x, const float y, const float z) {
        scalef.x += x;
        scalef.y += y;
        scalef.z += z;
    }
    void scale (const glm::vec3 vec) {
        scalef.x += vec.x;
        scalef.y += vec.y;
        scalef.z += vec.z;
    }
    void setTranslate (const float _x, const float _y, const float _z) {
        translatef.x = _x;
        translatef.y = _y;
        translatef.z = _z;
    }
    void setTranslate (const glm::vec3 _vec) {
        translatef = _vec;
    }
    void setRotate (const float _angle, const float _x, const float _y, const float _z) {
        anglef = _angle;
        rotatef.x = _x;
        rotatef.y = _y;
        rotatef.z = _z;
    }
    void setRotate (const float _angle, const glm::vec3 _vec) {
        anglef = _angle;
        rotatef = _vec;
    }
    void setScale (const float _x, const float _y, const float _z) {
        scalef.x = _x;
        scalef.y = _y;
        scalef.z = _z;
    }
    void setScale (const glm::vec3 _vec) {
        scalef = _vec;
    }
    glm::vec3 getTranslate () const {
        return translatef;
    }
    float getAngle () const {
        return anglef;
    }
    glm::vec3 getRotate () const {
        return rotatef;
    }
    glm::vec3 getScale () const {
        return scalef;
    }
    void setLongestSideTo (float len) {
        float longest = max(width, height);
        longest = max(longest, depth);
        float scaleFactor = len / longest;
        setScale(scaleFactor, scaleFactor, scaleFactor);
    }

public: // Colors
    void setColor (const float r, const float g, const float b, const float a) {
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }
    void setRandomColor () {
        color = glm::vec4(static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                          static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                          static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                          1.0f);
    }
    glm::vec4 getColor () const {
        return color;
    }

public:
    glm::vec3 getWorldPos () const {
        return translatef;
    }
    void setSpeed (const float _speed) {
        speed = _speed;
    }
    float getSpeed () const {
        return speed;
    }
    void move (const float angle) {
        GLfloat rad = getRadian(anglef + angle);
        GLfloat x = -speed * cos(rad);
        GLfloat z = speed * sin(rad);
        translate(x, 0.0f, z);
    }


private: // utilities
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
    void apply_material(const aiMaterial *mtl) {
        float c[4];

        GLenum fill_mode;
        int ret1, ret2;
        aiColor4D diffuse;
        aiColor4D specular;
        aiColor4D ambient;
        aiColor4D emission;
        ai_real shininess, strength;
        int two_sided;
        int wireframe;
        unsigned int max;

        set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
            color4_to_float4(&diffuse, c);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

        set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
            color4_to_float4(&specular, c);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

        set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
            color4_to_float4(&ambient, c);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

        set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
            color4_to_float4(&emission, c);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

        max = 1;
        ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
        if(ret1 == AI_SUCCESS) {
            max = 1;
            ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
            if(ret2 == AI_SUCCESS)
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
            else
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
        }
        else {
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
            set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
        }

        max = 1;
        if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
            fill_mode = wireframe ? GL_LINE : GL_FILL;
        else
            fill_mode = GL_FILL;
        glPolygonMode(GL_FRONT_AND_BACK, fill_mode);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        max = 1;
        if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
            glDisable(GL_CULL_FACE);
        else
            glEnable(GL_CULL_FACE);
    }
    void color4_to_float4(const aiColor4D *c, float f[4]) {
        f[0] = c->r;
        f[1] = c->g;
        f[2] = c->b;
        f[3] = c->a;
    }
    void set_float4(float f[4], float a, float b, float c, float d) {
        f[0] = a;
        f[1] = b;
        f[2] = c;
        f[3] = d;
    }
    void calculate_bounding_box(glm::vec3* min, glm::vec3* max)
    {
        aiMatrix4x4 trafo;
        aiIdentityMatrix4(&trafo);

        min->x = min->y = min->z =  1e10f;
        max->x = max->y = max->z = -1e10f;
        calculate_bounding_box_for_node(scene->mRootNode,min,max,&trafo);
    }
    void calculate_bounding_box_for_node (const aiNode* nd,
        glm::vec3* min,
        glm::vec3* max,
        aiMatrix4x4* trafo
    ) {
        aiMatrix4x4 prev;
        unsigned int n = 0, t;

        prev = *trafo;
        aiMultiplyMatrix4(trafo,&nd->mTransformation);

        for (; n < nd->mNumMeshes; ++n) {
            const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
            for (t = 0; t < mesh->mNumVertices; ++t) {

                aiVector3D tmp = mesh->mVertices[t];
                aiTransformVecByMatrix4(&tmp,trafo);

                min->x = min(min->x,tmp.x);
                min->y = min(min->y,tmp.y);
                min->z = min(min->z,tmp.z);

                max->x = max(max->x,tmp.x);
                max->y = max(max->y,tmp.y);
                max->z = max(max->z,tmp.z);
            }
        }

        for (n = 0; n < nd->mNumChildren; ++n) {
            calculate_bounding_box_for_node(nd->mChildren[n],min,max,trafo);
        }
        *trafo = prev;
    }

private: // Scene graph
    Object* parent;
    std::list<Object*> children;

private: // Mesh
    const aiScene* scene;
    glm::vec4 color;
    float width;
    float height;
    float depth;

private: // Factors of model-view matrix
    glm::vec3 translatef;
    glm::vec3 rotatef;
    glm::vec3 scalef;
    float anglef;

private: // Other properties
    float speed;
};

#endif