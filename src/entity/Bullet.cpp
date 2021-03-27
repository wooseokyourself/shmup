#include "entity/Bullet.hpp"

Bullet::Bullet () {
    root->init(CIRCLE);
}

Bullet::~Bullet () { }

void Bullet::init (const ModelViewMat2D& mat, const GLfloat radius, const Rgba color, const GLfloat speed) {
    Circle* shape = (Circle*)**root;
    shape->setMatrix(mat);
    shape->setRadius(radius);
    shape->setColor(color);
    setSpeed(speed);
}

void Bullet::display () const {
    root->display();
}