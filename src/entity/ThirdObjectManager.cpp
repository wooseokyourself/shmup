#include "entity/ThirdObjectManager.hpp"

ThirdObjectManager::ThirdObjectManager (const int _objectType) 
: objectType(_objectType) {
    for (int i = 0 ; i < 100 ; i ++) {
        Object* b;
        switch (objectType) {
            case BULLET:
                b = new Bullet();
                break;
            case ITEM:
                b = new Item();
                break;
        }
        pool.push(b);
        pushChild(b);
    }
}

ThirdObjectManager::~ThirdObjectManager () {
    while (!activeObjects.empty()) {
        if (activeObjects.back() != nullptr)
            delete activeObjects.back();
        activeObjects.pop_back();
    }
    while (!pool.empty()) {
        if (pool.top() != nullptr)
            delete pool.top();
        pool.pop();
    }
}

/**
 * @brief Construct a bullet in (x,y) position.
 */
void ThirdObjectManager::activateObject (const TransformMatrix& mat, const GLfloat param, const Rgba color, const GLfloat speed) {
    if (pool.empty())
        return;
    Object* object = pool.top();
    pool.pop();
    TransformMatrix objectInitMat = mat;
    switch (objectType) {
        case BULLET: {
            Bullet* bullet = (Bullet*)object;
            bullet->init(objectInitMat, param, color, speed);
            break;
        }
        case ITEM: {
            Item* item = (Item*)object;
            item->init(objectInitMat, param, color, speed);
            break;
        }
    }
    activeObjects.push_back(object);
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
    for (Object* object : activeObjects) {
        if (object->isIn(leftTop, rightBottom)) {
            pool.push(object);
            activeObjects.remove(object);
            return true;
        }
    }
    return false;
}

/**
 * @brief Manage all bullets; movement of all bullets, deactivating bullets which is out of bound.
 * This method must be called in all frame.
 * activateObject 메소드의 인자로 온 mat의 y방향으로 쭉 전진함.
 */
void ThirdObjectManager::update () {
    std::stack<Object*> deactivating;
    for (Object* object : activeObjects) {
        switch (objectType) {
        case BULLET: {
            Bullet* bullet = (Bullet*)object;
            if (bullet->isOutOfBound()) {
                deactivating.push(bullet);
                continue;
            }
            bullet->move(90.0f);
            break;
        }
        case ITEM: {
            Item* item = (Item*)object;
            if (item->isDurationTimeout()) {
                deactivating.push(item);
                continue;
            }
            item->move(90.0f);
            break;
        }
    }
    }
    while (!deactivating.empty()) {
        Object* object = deactivating.top();
        deactivating.pop();
        activeObjects.remove(object);
        pool.push(object);
    }
}

/**
 * @brief Draw all bullets in OpenGL world.
 */
void ThirdObjectManager::display () const {
    for (Object* object : activeObjects)
        object->display();
}