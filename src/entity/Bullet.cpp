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

void Bullet::move () {
    const ModelViewMat2D& mat = (**root)->getMatrix();
    GLfloat rad = getRadian(mat.degree + 90.0f);
    GLfloat x = speed * cos(rad);
    GLfloat y = speed * sin(rad);
    (**root)->translate(x, y);
}

void Bullet::display () const {
    root->display();
}