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
    Object () : parent(nullptr), renderDebug(false), speed(0.0f), drawFlag(false) {
        color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        translatef = glm::vec3(0.0f, 0.0f, 0.0f);
        scalef = glm::vec3(1.0f, 1.0f, 1.0f);
        modelViewMat = glm::mat4(1.0f);
    }
    virtual void update () {
        modelViewMat = glm::translate(glm::mat4(1.0f), translatef);
        for (int i = rotateAxisStack.size() - 1 ; i >= 0 ; i --)
            modelViewMat = modelViewMat * glm::rotate(glm::mat4(1.0f), getRadian(angleStack[i]), rotateAxisStack[i]);
        modelViewMat = modelViewMat * glm::scale(glm::mat4(1.0f), scalef); 
        for (Object* child : children)
            child->update();
    }
    virtual void draw () {
        glPushMatrix();
        glTranslatef(translatef.x, translatef.y, translatef.z);
        for (int i = rotateAxisStack.size() - 1 ; i >= 0 ; i --)
            glRotatef(angleStack[i], rotateAxisStack[i].x, rotateAxisStack[i].y, rotateAxisStack[i].z);
        glScalef(scalef.x, scalef.y, scalef.z);
        if (scene && drawFlag) {
            glColor4f(color.r, color.g, color.b, color.a);
            drawMeshes(scene, scene->mRootNode);

            if (renderDebug && bbVertices.size() == 8) {
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

public: // Model-view matrix factors
    void pasteModelViewMat (const Object& ref) {
        translatef = ref.translatef;
        rotateAxisStack = ref.rotateAxisStack;
        angleStack = ref.angleStack;
        scalef = ref.scalef;
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
    void rotate (const float angle, const float x, const float y, const float z) {
        if (angle != 0.0f) {
            rotateAxisStack.push_back(glm::vec3(x, y, z));
            angleStack.push_back(angle);
        }
    }
    void rotate (const float angle, const glm::vec3 axis) {
        if (angle != 0.0f) {
            rotateAxisStack.push_back(axis);
            angleStack.push_back(angle);
        }
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
        rotateAxisStack.clear();
        angleStack.clear();
        if (_angle != 0) {
            rotateAxisStack.push_back(glm::vec3(_x, _y, _z));
            angleStack.push_back(_angle);
        }
    }
    void setRotate (const float _angle, const glm::vec3 _axis) {
        rotateAxisStack.clear();
        angleStack.clear();
        if (_angle != 0.0f) {
            rotateAxisStack.push_back(_axis);
            angleStack.push_back(_angle);
        }
    }
    void setRotateStack (const std::vector<float> _angleStack, const std::vector<glm::vec3> _rotateAxisStack) {
        angleStack = _angleStack;
        rotateAxisStack = _rotateAxisStack;
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
    std::vector<float> getAngleStack () const {
        return angleStack;
    }
    std::vector<glm::vec3> getRotateAxisStack () const {
        return rotateAxisStack;
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

public: // Utilities
    void setDraw (bool flag) {
        drawFlag = flag;
    }
    glm::mat4 getModelViewMat () const {
        return modelViewMat;
    }
    glm::vec3 getNagativeZaxisDirection () const {
        return modelViewMat[2]; // third column
    }

public: // Colors
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
    void setRenderingDebug (bool flag) {
        renderDebug = flag;
        for (Object* child : children)
            child->setRenderingDebug(flag);
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
        glm::vec3 worldVecA = glm::vec3(modelViewMat * glm::vec4(bbMin, 1));
        glm::vec3 worldVecB = glm::vec3(modelViewMat * glm::vec4(bbMax, 1));
    
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
    void calculate_bounding_box () {
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
    bool renderDebug;
    glm::vec3 bbMin;
    glm::vec3 bbMax;
    std::vector<glm::vec3> bbVertices;
    float width;
    float height;
    float depth;

private: // Factors of model-view matrix
    glm::vec3 translatef;
    glm::vec3 scalef;
    std::vector<glm::vec3> rotateAxisStack;
    std::vector<float> angleStack;
    glm::mat4 modelViewMat;

private: // Other properties
    bool drawFlag;
    float speed;
};

#endif