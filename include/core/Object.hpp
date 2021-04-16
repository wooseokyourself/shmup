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

glm::vec3 rotateYaxis (const float angle, const glm::vec3 p) {
    const float t = getRadian(angle);
    return glm::vec3(p.x * cos(t) - p.z * sin(t), p.y, p.x * sin(t) + p.z * cos(t));
}

class Object {
public:
    Object () : parent(nullptr), renderBb(false), speed(0.0f), anglef(0.0f) {
        color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        translatef = glm::vec3(0.0f, 0.0f, 0.0f);
        rotatef = glm::vec3(0.0f, 0.0f, 0.0f);
        scalef = glm::vec3(1.0f, 1.0f, 1.0f);
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

            if (renderBb) {
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
            }
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
    void setLongestSideTo (const float len) {
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
    void loadModel (std::string path) {
        scene = aiImportFile(path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
        if (scene) {
            calculate_bounding_box();
            width = abs(bbMin.x - bbMax.x);
            height = abs(bbMin.y - bbMax.y);
            depth = abs(bbMin.z - bbMax.z);
            centerToLeftRatio = abs(bbMin.x) / width;
            centerToBelowRatio = abs(bbMin.y) / height;
            centerToFrontRatio = abs(bbMin.z) / depth;

            bbVertices.clear();
            bbVertices.push_back(glm::vec3(bbMin.x, bbMin.y, bbMax.z));
            bbVertices.push_back(glm::vec3(bbMax.x, bbMin.y, bbMax.z));
            bbVertices.push_back(glm::vec3(bbMax.x, bbMax.y, bbMax.z));
            bbVertices.push_back(glm::vec3(bbMin.x, bbMax.y, bbMax.z));
            bbVertices.push_back(glm::vec3(bbMin.x, bbMin.y, bbMin.z));
            bbVertices.push_back(glm::vec3(bbMax.x, bbMin.y, bbMin.z));
            bbVertices.push_back(glm::vec3(bbMax.x, bbMax.y, bbMin.z));
            bbVertices.push_back(glm::vec3(bbMin.x, bbMax.y, bbMin.z));
        }
        else
            std::cout << "model load failed" << std::endl;
    }
    glm::vec3 getWorldPos () const {
        return translatef;
    }
    void setRenderingBoundingBox (bool flag) {
        renderBb = flag;
    }
    std::vector<glm::vec3> getWorldBoundingBox () const { // 잉여, 아마 안 쓸듯
        // glm::vec3 pos = getWorldPos();
        glm::vec3 pos = rotateYaxis(anglef, glm::vec3(0.0f, 0.0f, 0.0f));
        glm::vec3 center;
        float nwidth = width * scalef.x, nheight = height * scalef.y, ndepth = depth * scalef.z; 
        float halfWidth = nwidth / 2.0f, halfHeight = nheight / 2.0f, halfDepth = ndepth / 2.0f;
        center.x = (-pos.x - centerToLeftRatio * nwidth) + halfWidth;
        center.y = (-pos.y - centerToBelowRatio * nheight) + halfHeight;
        center.z = (-pos.z - centerToFrontRatio * ndepth) + halfDepth;
        center.x += translatef.x;
        center.y += translatef.y;
        center.z += translatef.z;
        std::vector<glm::vec3> ret;
        ret.push_back(rotateYaxis(anglef, glm::vec3(center.x - halfWidth, center.y - halfHeight, center.z + halfDepth)));
        ret.push_back(rotateYaxis(anglef, glm::vec3(center.x + halfWidth, center.y - halfHeight, center.z + halfDepth)));
        ret.push_back(rotateYaxis(anglef, glm::vec3(center.x + halfWidth, center.y + halfHeight, center.z + halfDepth)));
        ret.push_back(rotateYaxis(anglef, glm::vec3(center.x - halfWidth, center.y + halfHeight, center.z + halfDepth)));
        ret.push_back(rotateYaxis(anglef, glm::vec3(center.x - halfWidth, center.y - halfHeight, center.z - halfDepth)));
        ret.push_back(rotateYaxis(anglef, glm::vec3(center.x + halfWidth, center.y - halfHeight, center.z - halfDepth)));
        ret.push_back(rotateYaxis(anglef, glm::vec3(center.x + halfWidth, center.y + halfHeight, center.z - halfDepth)));
        ret.push_back(rotateYaxis(anglef, glm::vec3(center.x - halfWidth, center.y + halfHeight, center.z - halfDepth)));
        return ret;
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
    void apply_material (const aiMaterial *mtl) {
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
    void color4_to_float4 (const aiColor4D *c, float f[4]) {
        f[0] = c->r;
        f[1] = c->g;
        f[2] = c->b;
        f[3] = c->a;
    }
    void set_float4 (float f[4], float a, float b, float c, float d) {
        f[0] = a;
        f[1] = b;
        f[2] = c;
        f[3] = d;
    }
    void calculate_bounding_box ()
    {
        aiMatrix4x4 trafo;
        aiIdentityMatrix4(&trafo);

        bbMin.x = bbMin.y = bbMin.z =  1e10f;
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

private: // Scene graph
    Object* parent;
    std::list<Object*> children;

private: // Mesh
    const aiScene* scene;
    glm::vec4 color;
    bool renderBb;
    glm::vec3 bbMin;
    glm::vec3 bbMax;
    std::vector<glm::vec3> bbVertices;
    float width;
    float height;
    float depth;
    float centerToLeftRatio;
    float centerToBelowRatio;
    float centerToFrontRatio;

private: // Factors of model-view matrix
    glm::vec3 translatef;
    glm::vec3 rotatef;
    glm::vec3 scalef;
    float anglef;

private: // Other properties
    float speed;
};

#endif