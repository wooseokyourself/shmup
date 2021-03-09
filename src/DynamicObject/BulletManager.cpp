#include "DynamicObject/BulletManager.hpp"

BulletManager::BulletManager (const GLfloat bulletWidth, const GLfloat bulletHeight, const GLfloat bulletSpeed) {
    for (int i = 0 ; i < MAX_BULLETS ; i ++) {
        Bullet* b = new Bullet(bulletWidth, bulletHeight, bulletSpeed);
        pool.push(b);
    }
}

BulletManager::~BulletManager () {
    while (!activeBullets.empty()) {
        delete activeBullets.back();
        activeBullets.pop_back();
    }
    while (!pool.empty()) {
        delete pool.top();
        pool.pop();
    }
}

void BulletManager::activateBullet (const GLfloat x, const GLfloat y) {
    if (pool.empty())
        return;
    Bullet* bullet = pool.top();
    pool.pop();
    bullet->setPosition(x, y);
    activeBullets.push_back(bullet);
}

void BulletManager::display () {
    for (Bullet* bullet : activeBullets)
        bullet->display(0.0f, 0.0f, 1.0f);
}

void BulletManager::update () {
    std::stack<Bullet*> deactivating;
    for (Bullet* bullet : activeBullets) {
        if (bullet->isOutOfBound()) {
            deactivating.push(bullet);
            continue;
        }
        bullet->moveUp();
    }
    while (!deactivating.empty()) {
        Bullet* bullet = deactivating.top();
        deactivating.pop();
        activeBullets.remove(bullet);
        pool.push(bullet);
    }
}

size_t BulletManager::activatedBulletsNumber () {
    return activeBullets.size();
}

bool BulletManager::deactivateBulletIfItsIn (const Point leftTop, const Point rightBottom) {
    for (Bullet* bullet : activeBullets) {
        Point bLeftTop = bullet->getLeftTop();
        Point bRightBottom = bullet->getRightBottom();
        if ( ((bLeftTop.x > rightBottom.x) || (bRightBottom.x < leftTop.x)
         || (bLeftTop.y < rightBottom.y) || (bRightBottom.y > leftTop.y)) == false ) {
            pool.push(bullet);
            activeBullets.remove(bullet);
            return true;
        }
    }
    return false;
}