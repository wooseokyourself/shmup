#include "dynamics/Airplane.hpp"

Airplane::BulletManager::BulletManager (const GLfloat bulletWidth, const GLfloat bulletHeight, const GLfloat bulletSpeed) {
    for (int i = 0 ; i < MAX_BULLETS ; i ++) {
        Bullet* b = new Bullet(bulletWidth, bulletHeight, bulletSpeed);
        pool.push(b);
    }
}

Airplane::BulletManager::~BulletManager () {
    while (!activeBullets.empty()) {
        delete activeBullets.back();
        activeBullets.pop_back();
    }
    while (!pool.empty()) {
        delete pool.top();
        pool.pop();
    }
}

void Airplane::BulletManager::activateBullet (const GLfloat x, const GLfloat y) {
    if (pool.empty())
        return;
    Bullet* bullet = pool.top();
    pool.pop();
    bullet->setPosition(x, y);
    activeBullets.push_back(bullet);
}

void Airplane::BulletManager::display (const GLfloat R, const GLfloat G, const GLfloat B) const {
    for (Bullet* bullet : activeBullets)
        bullet->display(R, G, B);
}

void Airplane::BulletManager::update (const int bulletDirection) {
    std::stack<Bullet*> deactivating;
    for (Bullet* bullet : activeBullets) {
        if (bullet->isOutOfBound(bulletDirection)) {
            deactivating.push(bullet);
            continue;
        }
        bullet->move(bulletDirection);
    }
    while (!deactivating.empty()) {
        Bullet* bullet = deactivating.top();
        deactivating.pop();
        activeBullets.remove(bullet);
        pool.push(bullet);
    }
}

size_t Airplane::BulletManager::activatedBulletsNumber () {
    return activeBullets.size();
}

bool Airplane::BulletManager::deactivateBulletIfItsIn (const Point leftTop, const Point rightBottom) {
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

Airplane::Airplane (const Point p,
                    const GLfloat _width, 
                    const GLfloat _height, 
                    const GLfloat _speed, 
                    const GLfloat bulletSpeed) 
: DynamicObject(p, _width, _height, _speed), 
  bulletManager(0.1f, 0.1f, bulletSpeed), 
  lives(0), 
  lastActivatedTime(0), 
  lastDeactivatedTime(0) { }

Airplane::Airplane (const GLfloat _x, 
                    const GLfloat _y, 
                    const GLfloat _width, 
                    const GLfloat _height, 
                    const GLfloat _speed, 
                    const GLfloat bulletSpeed) 
: DynamicObject(_x, _y, _width, _height, _speed), 
  bulletManager(0.05f, 0.05f, bulletSpeed), 
  lives(0), 
  lastActivatedTime(0), 
  lastDeactivatedTime(0) { }

void Airplane::update (const int bulletDirection) {
    bulletManager.update(bulletDirection);
}

void Airplane::init (const uint8_t _lives) {
    if (isAlive())
        return;
    lives = _lives;
    lastActivatedTime = glutGet(GLUT_ELAPSED_TIME);
}

void Airplane::destruct () {
    std::cout << "Airplane Destructed!" << std::endl;
    lives = 0;
    lastDeactivatedTime = glutGet(GLUT_ELAPSED_TIME);
}

void Airplane::loseLife () {
    if (--lives <= 0)
        destruct();
}

bool Airplane::isAlive () const {
    return lives > 0;
}

void Airplane::fire () {
    bulletManager.activateBullet(x, y);
}

void Airplane::display () const {
    bulletManager.display(color.R + 0.25f, color.G + 0.25f, color.B + 0.25f);
    if (isAlive())
        Rectangle::display(color);
}

int Airplane::getLastActivatedTime () const {
    return lastActivatedTime;
}

int Airplane::getLastDeactivatedTime () const {
    return lastDeactivatedTime;
}