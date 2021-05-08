#include "StraightMovingObjectManager.hpp"

StraightMovingObjectManager::StraightMovingObjectManager (const int maxPool) {
    for (int i = 0; i < maxPool; i++)
        pool.push(new ModelViewMat);
    objectFront = glm::vec3(0.0f, 0.0f, 1.0f);
}

StraightMovingObjectManager::~StraightMovingObjectManager() {
    while (!pool.empty()) {
        ModelViewMat* mat = pool.top();
        pool.pop();
        delete mat;
    }
    while (!activatedObjectMat.empty()) {
        ModelViewMat* mat = activatedObjectMat.back();
        activatedObjectMat.pop_back();
        delete mat;
    }
}

void StraightMovingObjectManager::update () {
    std::stack<ModelViewMat*> deactivating;
    for (ModelViewMat* mat : activatedObjectMat) {
        if (isPointOutOfWorld(mat->getTranslate(), AXIS_LIMIT_ABS)) {
            deactivating.push(mat);
            continue;
        }
        glm::vec4 unit = mat->get() * glm::vec4(objectFront, 0);
        mat->translate(glm::vec3(unit / glm::length(glm::vec3(unit)) * getSpeed()));
        mat->update();
    }
    while (!deactivating.empty()) {
        ModelViewMat* mat = deactivating.top();
        deactivating.pop();
        activatedObjectMat.remove(mat);
        pool.push(mat);
    }
}

void StraightMovingObjectManager::display (const glm::mat4& viewProjectionMat, const glm::mat4& parentModelViewMat) {
    setDraw(true);
    for (ModelViewMat* mat : activatedObjectMat) {
        modelViewMat = *mat;
        Object::display(viewProjectionMat, glm::mat4(1.0f));
    }
    setDraw(false);
}

void StraightMovingObjectManager::init(const glm::vec3 straightVec, const glm::vec4 color, const float speed) {
    objectFront = straightVec;
    setColor(color);
    setSpeed(speed);
}

void StraightMovingObjectManager::activateObject (const ModelViewMat& initTransform, const float maxSide) {
    if (pool.empty())
        return;
    ModelViewMat* mat = pool.top();
    pool.pop();
    *mat = initTransform; 
    mat->setScale((maxSide / longestSide) / inheritedScalef);
    activatedObjectMat.push_back(mat);
}

size_t StraightMovingObjectManager::getActivatedObjectsNumber () const {
    return activatedObjectMat.size();
}

bool StraightMovingObjectManager::deactivateObjectWhichIsIn (Object* targetBox) {
    bool ret = false;
    std::stack<ModelViewMat*> deactivating;
    for (ModelViewMat* mat : activatedObjectMat) {
        if (targetBox->isIn(mat->getTranslate())) {
            ret = true;
            deactivating.push(mat);
            continue;
        }
    }
    while (!deactivating.empty()) {
        ModelViewMat* mat = deactivating.top();
        deactivating.pop();
        activatedObjectMat.remove(mat);
        pool.push(mat);
    }
    return ret;
}

bool StraightMovingObjectManager::isPointOutOfWorld(const glm::vec3& p, const float axisLimitAbs) {
    return (
        p.x < -axisLimitAbs || p.x > axisLimitAbs ||
        p.y < -axisLimitAbs || p.y > axisLimitAbs ||
        p.z < -axisLimitAbs || p.z > axisLimitAbs
        );
}