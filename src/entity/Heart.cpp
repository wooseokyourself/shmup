#include "entity/Heart.hpp"

Heart::Heart () {
    bottom = pushChild(FigureType::RECT);
    left = pushChild(FigureType::CIRCLE);
    right = pushChild(FigureType::CIRCLE);
}

void Heart::init (const TransformMatrix& mat, const GLfloat unit, const Rgba color) {
    const GLfloat m = 0.353553 * unit; // sqrt(2) / 4 * unit

    setMatrix(mat);
    ((Rect*)**bottom)->setSide(unit, unit);
    ((Circle*)**left)->setRadius(unit / 2.0f);
    ((Circle*)**right)->setRadius(unit / 2.0f);

    bottom->setRotate(45.0f);
    left->setTranslate(m, m);
    right->setTranslate(-m, m);

    bottom->setColor(color);
    left->setColor(color);
    right->setColor(color);
}