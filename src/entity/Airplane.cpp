#include "entity/Airplane.hpp"

/**
 * @param p The center point axis of the airplane. (each are -1.0 to 1.0)
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 * @param _speed (-1.0 to 1.0)
 * @param bulletSpeed (-1.0 to 1.0)
 */
Airplane::Airplane (const Point2D p,
                    const GLfloat width, 
                    const GLfloat height, 
                    const GLfloat speed, 
                    const GLfloat _bulletSpeed) 
: bulletManager(BULLET),
  bulletSpeed(_bulletSpeed),
  lives(0), 
  lastActivatedTime(0), 
  lastDeactivatedTime(0) {
    setPosition(p);
    setSide(width, height);
    setSpeed(speed);
}

/**
 * @param _x The x value of the center point of the airplane. (-1.0 to 1.0)
 * @param _y The y value of the center point of the airplane. (-1.0 to 1.0)
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 * @param _speed (-1.0 to 1.0)
 * @param bulletSpeed (-1.0 to 1.0)
 */
Airplane::Airplane (const GLfloat x, 
                    const GLfloat y, 
                    const GLfloat width, 
                    const GLfloat height, 
                    const GLfloat speed, 
                    const GLfloat _bulletSpeed) 
: bulletManager(BULLET), 
  bulletSpeed(_bulletSpeed), 
  lives(0), 
  lastActivatedTime(0), 
  lastDeactivatedTime(0) {
    setPosition(x, y);
    setSide(width, height);
    setSpeed(speed);
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
        bulletManager.activateObject(mat, 0.025, Rgba(color.R + 0.15f, color.G + 0.15f, color.B + 0.15f), bulletSpeed);
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

/**
 * @brief Draw the airplane and its bullets in OpenGL world.
 */
void Airplane::display () {
    bulletManager.display();
    if (isAlive())
        Rect::display();
}
