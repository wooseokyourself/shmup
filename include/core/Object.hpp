#ifndef __OBJECT__
#define __OBJECT__

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "core/Mesh.hpp"

class Object {
public:
    Object () : parent(nullptr), speed(0.0f), drawFlag(false) {
        translatef = glm::vec3(0.0f, 0.0f, 0.0f);
        scalef = 1.0f;
        inheritedScalef = 1.0f;
        modelViewMat = glm::mat4(1.0f);
    }
    virtual void update () {
        modelViewMat = glm::translate(glm::mat4(1.0f), translatef);
        for (int i = rotateAxisStack.size() - 1 ; i >= 0 ; i --)
            modelViewMat = glm::rotate(modelViewMat, getRadian(angleStack[i]), rotateAxisStack[i]);
        modelViewMat = glm::scale(modelViewMat, glm::vec3(scalef, scalef, scalef)); 
        for (Object* child : children) {
            child->inheritedScalef = inheritedScalef * scalef;
            child->update();
        }
    }
    virtual void draw () {
        glPushMatrix();
        glTranslatef(translatef.x, translatef.y, translatef.z);
        glScalef(scalef, scalef, scalef);
        for (int i = rotateAxisStack.size() - 1 ; i >= 0 ; i --)
            glRotatef(angleStack[i], rotateAxisStack[i].x, rotateAxisStack[i].y, rotateAxisStack[i].z);
        if (drawFlag)
            mesh.draw();
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
    std::list<Object*>& getChildren () {
        return children;
    }
    Object* getParent () {
        return parent;
    }
    
public: // Model-view matrix factors
    void translate (const float x, const float y, const float z) {
        translatef.x += x / inheritedScalef;
        translatef.y += y / inheritedScalef;
        translatef.z += z / inheritedScalef;
    }
    void translate (const glm::vec3 vec) {
        translatef.x += vec.x / inheritedScalef;
        translatef.y += vec.y / inheritedScalef;
        translatef.z += vec.z / inheritedScalef;
    }
    void setTranslate (const float _x, const float _y, const float _z) {
        translatef.x = _x / inheritedScalef;
        translatef.y = _y / inheritedScalef;
        translatef.z = _z / inheritedScalef;
    }
    void setTranslate (const glm::vec3 _vec) {
        translatef = _vec / inheritedScalef;
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
    glm::vec3 getTranslate () const {
        return translatef;
    }
    std::vector<float> getAngleStack () const {
        return angleStack;
    }
    std::vector<glm::vec3> getRotateAxisStack () const {
        return rotateAxisStack;
    }
    void setLongestSideTo (const float len) {
        scalef = (len / mesh.getLongestSide()) / inheritedScalef;
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

public: // Colors
    void setColor (const float r, const float g, const float b, const float a) {
        mesh.setColor(r, g, b, a);
    }
    void setColor (const glm::vec4 _color) {
        mesh.setColor(_color);
    }
    void setRandomColor () {
        mesh.setRandomColor();
    }
    glm::vec4 getColor () const {
        return mesh.getColor();
    }

public:
    void loadModel (std::string path) {
        if (!mesh.loadModel(path))
            std::cout << "model load failed" << std::endl;
    }
    glm::vec3 getWorldPos () const {
        return translatef;
    }
    void setWireframe (bool flag) {
        mesh.setWireframe (flag);
        for (Object* child : children)
            child->setWireframe(flag);
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



private: // Scene graph
    Object* parent;
    std::list<Object*> children;

private: // Mesh
    Mesh mesh;

private: // Factors of model-view matrix
    glm::vec3 translatef;
    float scalef;
    float inheritedScalef;
    std::vector<glm::vec3> rotateAxisStack;
    std::vector<float> angleStack;
    glm::mat4 modelViewMat;

private: // Other properties
    bool drawFlag;
    float speed;
};

#endif