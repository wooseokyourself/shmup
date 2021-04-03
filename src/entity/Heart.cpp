#include "entity/Heart.hpp"

Heart::Heart () {
    bottom = pushChild(RECT, FRONT);
    left = pushChild(CIRCLE, FRONT);
    right = pushChild(CIRCLE, FRONT);
}

Heart::~Heart () { }

void Heart::init (const TransformMatrix& mat, const GLfloat unit, const Rgba color) {
    const GLfloat m = 0.353553 * unit; // sqrt(2) / 4 * unit

    setMatrix(mat);
    ((Rect*)**bottom)->setSide(unit, unit);
    ((Circle*)**left)->setRadius(unit / 2.0f);
    ((Circle*)**right)->setRadius(unit / 2.0f);

    bottom->rotate(45.0f);
    left->translate(m, m);
    right->translate(-m, m);

    bottom->setColor(color);
    left->setColor(color);
    right->setColor(color);
}

void Heart::update () {
    Object::update();
}

void Heart::display () const {
    Object::display();
}