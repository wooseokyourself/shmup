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

size_t ThirdObjectManager::getActivatedObjectsNumber () const {
    return activeObjects.size();
}

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

void ThirdObjectManager::display () const {
    for (Object* object : activeObjects)
        object->display();
}