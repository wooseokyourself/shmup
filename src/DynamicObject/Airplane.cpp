#include "DynamicObject/Airplane.hpp"

Airplane::Airplane (const Point p, const GLfloat _width, const GLfloat _height, const GLfloat _speed)
: DynamicObject(p, _width, _height, _speed), bulletManager(0.1f, 0.1f, 0.05f), lives(0), activated(false) {

}

Airplane::Airplane (const GLfloat _x, const GLfloat _y, const GLfloat _width, const GLfloat _height, const GLfloat _speed) 
: DynamicObject(_x, _y, _width, _height, _speed), bulletManager(0.05f, 0.05f, 0.05f), lives(0), activated(false) {

}

void Airplane::init (const uint8_t _lives) {
    if (activated)
        return;
    activated = true;
    lives = _lives;
}

bool Airplane::isActivated () {
    return activated;
}

void Airplane::destruct () {
    std::cout << "Airplane Destructed!" << std::endl;
    activated = false;
}

void Airplane::loseLife () {
    --lives;
    if (lives == 0)
        destruct();
}

void Airplane::moveLeft () {
    if (x > -1)
        DynamicObject::moveLeft(); 
}

void Airplane::moveRight () {
    if (x < 1)
        DynamicObject::moveRight();
}

void Airplane::moveUp () { 
    if (y < 1)
        DynamicObject::moveUp();
}

void Airplane::moveDown () {
    if (y > -1)
        DynamicObject::moveDown();
}

void Airplane::fire () {
    bulletManager.activateBullet(x, y);
}

void Airplane::display () {
    if (!activated)
        return;
    bulletManager.display();
    DynamicObject::display(1.0f, 0.0f, 0.0f);
}

/**
 * @brief Call in idle.
 */
void Airplane::update () {
    bulletManager.update();
}