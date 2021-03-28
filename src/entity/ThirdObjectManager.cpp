#include "entity/ThirdObjectManager.hpp"

ThirdObjectManager::ThirdObjectManager (const int _objectType) 
: objectType(_objectType) {
    switch (objectType) {
        case BULLET:
            for (int i = 0 ; i < 100 ; i ++) {
                Object* b = new Bullet();
                pool.push(b);
            }
            break;
        case ITEM:
            for (int i = 0 ; i < 5 ; i ++) {
                Object* b = new Item();
                pool.push(b);
            }
            break;
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
void ThirdObjectManager::activateObject (const ModelViewMat2D& mat, const GLfloat param, const Rgba color, const GLfloat speed) {
    if (pool.empty())
        return;
    Object* object = pool.top();
    pool.pop();
    switch (objectType) {
        case BULLET: {
            Bullet* bullet = (Bullet*)object;
            bullet->init(mat, param, color, speed);
            break;
        }
        case ITEM: {
            Item* item = (Item*)object;
            item->init(mat, param, color, speed);
            break;
        }
    }
    activeObjects.push_back(object);
}

/**
 * @brief Draw all bullets in OpenGL world.
 */
void ThirdObjectManager::display () const {
    for (Object* object : activeObjects)
        object->display();
}

/**
 * @brief Manage all bullets; movement of all bullets, deactivating bullets which is out of bound.
 * This method must be called in all frame.
 * activateObject 메소드의 인자로 온 mat의 y방향으로 쭉 전진함.
 */
void ThirdObjectManager::update () {
    std::stack<Object*> deactivating;
    for (Object* object : activeObjects) {
        if (object->isOutOfBound()) {
            deactivating.push(object);
            continue;
        }
        switch (objectType) {
        case BULLET: {
            Bullet* bullet = (Bullet*)object;
            bullet->move();
            break;
        }
        case ITEM: {
            Item* item = (Item*)object;
            item->move();
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
