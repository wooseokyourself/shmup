#ifndef __STRAIGHTMOVINGOBJECTMANAGER__
#define __STRAIGHTMOVINGOBJECTMANAGER__

#include <stack>

#include "core/Object.hpp"
#include "World.hpp"

class Bullet;
class Item;

class StraightMovingObjectManager : public Object {
public:
    StraightMovingObjectManager (const int maxPool, const std::string objectModelPath, const glm::vec3 _objectFront) {
        for (int i = 0 ; i < maxPool ; i ++) {
            Object* geometric = new Object;
            Object* object = new Object;
            object->loadModel(objectModelPath); // 직선운동 와중에 자전하기위함
            geometric->pushChild(object);
            pool.push(object);
            pushChild(object);
        }
        objectFront = _objectFront;
    }
    ~StraightMovingObjectManager () {
        while (!activatedObjects.empty()) {
            if (activatedObjects.back() != nullptr)
                delete activatedObjects.back();
            activatedObjects.pop_back();
        }
        while (!pool.empty()) {
            if (pool.top() != nullptr)
                delete pool.top();
            pool.pop();
        }
    }
    virtual void update () {
        std::stack<Object*> deactivating;
        for (Object* object : activatedObjects) {
            Object* geometric = object->getParent();
            geometric->update();
            if (geometric->isCenterOutOfWorld(AXIS_LIMIT_ABS)) {
                deactivating.push(object);
                continue;
            }
            geometric->move(objectFront);
        }
        while (!deactivating.empty()) {
            Object* object = deactivating.top();
            deactivating.pop();
            activatedObjects.remove(object);
            pool.push(object);
            object->setDraw(false);
        }
    }
    virtual void draw () {
        for (Object* object : activatedObjects)
            object->getParent()->draw();
    }
    void activateObject (const glm::vec3 translate,
                         const float rotateAngle,
                         const glm::vec3 rotateAxis, 
                         const float maxSide, 
                         const glm::vec4 color, 
                         const GLfloat speed) {
        std::cout << "activateObject start" << std::endl;
        if (pool.empty())
            return;
        Object* object = pool.top();
        Object* geometric = object->getParent();
        pool.pop();
        activatedObjects.push_back(object);
        geometric->setTranslate(translate);
        geometric->setRotate(rotateAngle, rotateAxis);
        geometric->setSpeed(speed);
        object->setLongestSideTo(maxSide);
        object->setColor(color);
        object->setDraw(true);
        std::cout << "activateObject end" << std::endl;
    }
    size_t getActivatedObjectsNumber () const {
        return activatedObjects.size();
    }
    bool deactivateObjectWhichIsIn (const Object* targetBox) {
        bool ret = false;
        std::stack<Object*> deactivating;
        for (Object* object : activatedObjects) {
            if (targetBox->isIn(object->getWorldPos())) {
                ret = true;
                deactivating.push(object);
                continue;
            }
        }
        while (!deactivating.empty()) {
            Object* object = deactivating.top();
            deactivating.pop();
            activatedObjects.remove(object);
            pool.push(object);
            object->setDraw(false);
        }
        return ret;
    }
    void setAutoRotation (const float anglePerFrame, const glm::vec3 axis) {
        for (Object* object : activatedObjects) {
            // setTranslate(-axis);
        }
    }

private:
    std::list<Object*> activatedObjects;
    std::stack<Object*> pool;
    glm::vec3 objectFront; // object front in model frame
};

#endif