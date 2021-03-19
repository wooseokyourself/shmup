#include "dynamics/Airplane.hpp"

Airplane::BulletManager::BulletManager (const GLfloat bulletRadius,
                                        const GLfloat bulletSpeed) {
    for (int i = 0 ; i < MAX_BULLETS ; i ++) {
        Bullet* b = new Bullet(bulletRadius, bulletSpeed);
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

/**
 * @brief Construct a bullet in (x,y) position.
 */
void Airplane::BulletManager::activateBullet (const ModelViewMat2D& mat, const Rgba color) {
    if (pool.empty())
        return;
    Bullet* bullet = pool.top();
    pool.pop();
    bullet->setPosition(mat.tx, mat.ty);
    /* 차후 비행기 각도 조절이 가능하면 bullet->mat = mat 으로 해야할 듯 */
    bullet->setColor(color);
    activeBullets.push_back(bullet);
}

/**
 * @brief Draw all bullets in OpenGL world.
 */
void Airplane::BulletManager::display () const {
    for (Bullet* bullet : activeBullets)
        bullet->display();
}

/**
 * @brief Manage all bullets; movement of all bullets, deactivating bullets which is out of bound.
 * This method must be called in all frame.
 * @param bulletDirection The direction of all bullets; LEFT, RIGHT, UP, DOWN, LEFT_UP, UP_RIGHT, RIGHT_DOWN, DOWN_LEFT
 */
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

/**
 * @return The number of existing bullets.
 */
size_t Airplane::BulletManager::getActivatedBulletsNumber () const {
    return activeBullets.size();
}

/**
 * @brief Remove bullets which are in the rectangle constructed by left-top and right-bottom points.
 * @param leftTop The left-top point of the target range in world space.
 * @param rightBottom The right-bottom point of the target range in world space.
 * @return false if no bullet removed.
 */
bool Airplane::BulletManager::deactivateBulletWhichIsIn (const Point2D leftTop, const Point2D rightBottom) {
    for (Bullet* bullet : activeBullets) {
        if (bullet->isIn(leftTop, rightBottom)) {
            pool.push(bullet);
            activeBullets.remove(bullet);
            return true;
        }
    }
    return false;
}

/**
 * @param p The center point axis of the airplane. (each are -1.0 to 1.0)
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 * @param _speed (-1.0 to 1.0)
 * @param bulletSpeed (-1.0 to 1.0)
 */
Airplane::Airplane (const Point2D p,
                    const GLfloat _width, 
                    const GLfloat _height, 
                    const GLfloat _speed, 
                    const GLfloat bulletSpeed) 
: Rect(p, _width, _height), 
  bulletManager(0.025f, bulletSpeed), 
  lives(0), 
  lastActivatedTime(0), 
  lastDeactivatedTime(0) {
    setSpeed(_speed);
}

/**
 * @param _x The x value of the center point of the airplane. (-1.0 to 1.0)
 * @param _y The y value of the center point of the airplane. (-1.0 to 1.0)
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 * @param _speed (-1.0 to 1.0)
 * @param bulletSpeed (-1.0 to 1.0)
 */
Airplane::Airplane (const GLfloat _x, 
                    const GLfloat _y, 
                    const GLfloat _width, 
                    const GLfloat _height, 
                    const GLfloat _speed, 
                    const GLfloat bulletSpeed) 
: Rect(_x, _y, _width, _height), 
  bulletManager(0.025f, bulletSpeed), 
  lives(0), 
  lastActivatedTime(0), 
  lastDeactivatedTime(0) {
    setSpeed(_speed);
}

/**
 * @brief Manage all bullets; movement of all bullets, deactivating bullets which is out of bound.
 * This method must be called in all frame.
 * @param bulletDirection The direction of all bullets; LEFT, RIGHT, UP, DOWN, LEFT_UP, UP_RIGHT, RIGHT_DOWN, DOWN_LEFT
 */
void Airplane::update (const int bulletDirection) {
    bulletManager.update(bulletDirection);
}

/**
 * @brief Construct the airplane.
 * @param _lives The number of lives of the airplane.
 */
void Airplane::init (const uint8_t _lives) {
    if (isAlive())
        return;
    lives = _lives;
    lastActivatedTime = glutGet(GLUT_ELAPSED_TIME);
}

/**
 * @brief Destruct the airplane.
 */
void Airplane::destruct () {
    std::cout << "Airplane Destructed!" << std::endl;
    lives = 0;
    lastDeactivatedTime = glutGet(GLUT_ELAPSED_TIME);
}

/**
 * @brief Subtract a life of the airplane. If the airplane's life is 0, the airplane will be destructed.
 */
void Airplane::loseLife () {
    if (--lives <= 0)
        destruct();
}

/**
 * @return true if the airplane was not destructed.
 */
bool Airplane::isAlive () const {
    return lives > 0;
}

int Airplane::getLives () const {
    return lives;
}

/**
 * @brief Fire a bullet.
 */
void Airplane::fire () {
    if (isAlive())
        bulletManager.activateBullet(mat, Rgba(color.R + 0.15f, color.G + 0.15f, color.B + 0.15f));
}

/**
 * @brief Draw the airplane and its bullets in OpenGL world.
 */
void Airplane::display () const {
    bulletManager.display();
    if (isAlive())
        Rect::display();
}

/**
 * @return The last constructed time of the airplane.
 * The time is the elapsed time from the process executed.
 */
int Airplane::getLastActivatedTime () const {
    return lastActivatedTime;
}

/**
 * @return The last destructed time of the airplane.
 * The time is the elapsed time from the process executed.
 */
int Airplane::getLastDeactivatedTime () const {
    return lastDeactivatedTime;
}