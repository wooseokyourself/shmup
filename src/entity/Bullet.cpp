#include "entity/Bullet.hpp"

Bullet::Bullet ()
: outOfBound(false) {
    root->init(CIRCLE);
}

Bullet::~Bullet () { }

void Bullet::init (const ModelViewMat2D& mat, const GLfloat radius, const Rgba color, const GLfloat speed) {
    Circle* shape = (Circle*)**root;
    shape->setMatrix(mat);
    shape->setRadius(radius);
    shape->setColor(color);
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

void Bullet::display () const {
    root->display();
}