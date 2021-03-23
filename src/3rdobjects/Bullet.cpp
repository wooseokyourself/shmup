#include "3rdobjects/Bullet.hpp"

void Bullet::init (const GLfloat radius, const ModelViewMat2D& mat, const Rgba color, const GLfloat speed) {
    setMatrix(mat);
    shape.setRadius(radius);
    shape.setColor(color);
    setSpeed(speed);
}

void Bullet::display () {
    shape.setPosition(mat.tx, mat.ty);
    shape.display();
}