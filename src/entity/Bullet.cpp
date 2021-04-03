#include "entity/Bullet.hpp"

Bullet::Bullet ()
: outOfBound(false) {
    setFigure(CIRCLE);
}

void Bullet::init (const TransformMatrix& mat, const GLfloat radius, const Rgba color, const GLfloat speed) {
    Circle* shape = (Circle*)**this;
    shape->setRadius(radius);
    setMatrix(mat);
    setColor(color);
    setSpeed(speed);
    outOfBound = false;
}

bool Bullet::isOutOfBound () const {
    return outOfBound;
}

void Bullet::handlingWhenOutOfBound () {
    if (isCenterOutOfBound())
        outOfBound = true;
}

void Bullet::update () {
    Object::update();
}

void Bullet::display () const {
    Object::display();
}