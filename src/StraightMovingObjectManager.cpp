#include "StraightMovingObjectManager.hpp"

StraightMovingObjectManager::StraightMovingObjectManager (const std::string& vertPath, const std::string& fragPath, const int maxPool, const std::string objectModelPath, const glm::vec3 _objectFront) {
    loadShader(vertPath, fragPath);
    for (int i = 0 ; i < maxPool ; i ++) {
        Object* object = new Object;
        object->setShader(shader);
        object->loadModel(objectModelPath);
        pool.push(object);
        pushChild(object);
    }
    objectFront = _objectFront;
}

StraightMovingObjectManager::~StraightMovingObjectManager () {
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

void StraightMovingObjectManager::update () {
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

void StraightMovingObjectManager::display (const glm::mat4& projection, const glm::mat4& lookAt, const glm::mat4& prevMat) {
    for (Object* object : activatedObjects)
        object->display(projection, lookAt, prevMat);
}

void StraightMovingObjectManager::activateObject (const glm::vec3 translate,
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

size_t StraightMovingObjectManager::getActivatedObjectsNumber () const {
    return activatedObjects.size();
}

bool StraightMovingObjectManager::deactivateObjectWhichIsIn (const Object* targetBox) {
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

void StraightMovingObjectManager::setAutoRotation (const float anglePerFrame, const glm::vec3 axis) {
    for (Object* object : activatedObjects) {
        // setTranslate(-axis);
    }
}