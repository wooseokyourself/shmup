#include "base/ThirdObjectManager.hpp"

ThirdObjectManager::ThirdObjectManager (const int objectType) {
    switch (objectType) {
        case BULLET:
            for (int i = 0 ; i < 100 ; i ++) {
                ThirdObject* b = new Bullet();
                pool.push(b);
            }
            break;
        case ITEM:
            for (int i = 0 ; i < 5 ; i ++) {
                ThirdObject* b = new Item();
                pool.push(b);
            }
            break;
    }
}

ThirdObjectManager::~ThirdObjectManager () {
    while (!activeObjects.empty()) {
        delete activeObjects.back();
        activeObjects.pop_back();
    }
    while (!pool.empty()) {
        delete pool.top();
        pool.pop();
    }
}

/**
 * @brief Construct a bullet in (x,y) position.
 */
void ThirdObjectManager::activateObject (const ModelViewMat2D& mat, const GLfloat param, const Rgba color, const GLfloat speed) {
    if (pool.empty())
        return;
    ThirdObject* object = pool.top();
    pool.pop();
    object->init(param, mat, color, speed);
    activeObjects.push_back(object);
}

/**
 * @brief Draw all bullets in OpenGL world.
 */
void ThirdObjectManager::display () const {
    for (ThirdObject* object : activeObjects)
        object->display();
}

/**
 * @brief Manage all bullets; movement of all bullets, deactivating bullets which is out of bound.
 * This method must be called in all frame.
 * @param bulletDirection The direction of all bullets; LEFT, RIGHT, UP, DOWN, LEFT_UP, UP_RIGHT, RIGHT_DOWN, DOWN_LEFT
 */
void ThirdObjectManager::update (const int direction) {
    std::stack<ThirdObject*> deactivating;
    for (ThirdObject* object : activeObjects) {
        if (object->isOutOfBound(direction)) {
            deactivating.push(object);
            continue;
        }
        object->move(direction);
    }
    while (!deactivating.empty()) {
        ThirdObject* object = deactivating.top();
        deactivating.pop();
        activeObjects.remove(object);
        pool.push(object);
    }
}

/**
 * @return The number of existing bullets.
 */
size_t ThirdObjectManager::getActivatedObjectsNumber () const {
    return activeObjects.size();
}

/**
 * @brief Remove bullets which are in the rectangle constructed by left-top and right-bottom points.
 * @param leftTop The left-top point of the target range in world space.
 * @param rightBottom The right-bottom point of the target range in world space.
 * @return false if no bullet removed.
 */
bool ThirdObjectManager::deactivateObjectWhichIsIn (const Point2D leftTop, const Point2D rightBottom) {
    for (ThirdObject* object : activeObjects) {
        if (object->isIn(leftTop, rightBottom)) {
            pool.push(object);
            activeObjects.remove(object);
            return true;
        }
    }
    return false;
}
