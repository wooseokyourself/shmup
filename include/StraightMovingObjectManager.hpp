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
            Object* b = new Object;
            b->loadModel(objectModelPath);
            pool.push(b);
            pushChild(b);
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
            object->update();
            if (object->isCenterOutOfWorld(AXIS_LIMIT_ABS)) {
                deactivating.push(object);
                continue;
            }
            object->move(objectFront);
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
            object->draw();
    }
    void activateObject (const glm::vec3 translate,
                         const std::vector<float> angleStack,
                         const std::vector<glm::vec3> rotateAxisStack, 
                         const float maxSide, 
                         const glm::vec4 color, 
                         const GLfloat speed) {
        if (pool.empty())
            return;
        Object* object = pool.top();
        pool.pop();
        activatedObjects.push_back(object);
        object->setTranslate(translate);
        object->setRotateStack(angleStack, rotateAxisStack);
        object->setLongestSideTo(maxSide);
        object->setColor(color);
        object->setSpeed(speed);
        object->setDraw(true);
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

private:
    std::list<Object*> activatedObjects;
    std::stack<Object*> pool;
    glm::vec3 objectFront; // object front in model frame
};

#endif