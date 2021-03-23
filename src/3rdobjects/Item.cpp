#include "3rdobjects/Item.hpp"

void Item::init (const GLfloat length, const ModelViewMat2D& mat, const Rgba color, const GLfloat speed) {
    setMatrix(mat);
    setSpeed(speed);
    radius = length / 2.0f;
    top.setRadius(radius);
    bottom.setRadius(radius);
    top.setColor(color);
    bottom.setColor(color);
    top.rotate(330);
    bottom.rotate(150);
}

void Item::display () {
    GLfloat b = radius / 2.0f;
    top.setPosition(mat.tx, mat.ty + b);
    bottom.setPosition(mat.tx, mat.ty - b);
    top.display();
    bottom.display();
}