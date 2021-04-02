#include "entity/Heart.hpp"

Heart::Heart () {
    root->init(RECT);
    bottom = (Rect*)**(root->addChild(RECT));
    left = (Circle*)**(root->addChild(CIRCLE));
    right = (Circle*)**(root->addChild(CIRCLE));
}

Heart::~Heart () { }

void Heart::init (const ModelViewMat2D& mat, const GLfloat unit, const Rgba color) {
    (**root)->setMatrix(mat);
    bottom->setSide(unit, unit);
    bottom->rotate(45.0f);
    left->setRadius(unit / 2.0f);
    right->setRadius(unit / 2.0f);
    const GLfloat m = 0.353553 * unit; // sqrt(2) / 4 * unit
    left->translate(m, m);
    right->translate(-m, m);

    (**root)->setColor(color);
    bottom->setColor(color);
    left->setColor(color);
    right->setColor(color);
}

void Heart::handlingWhenOutOfBound () { }

void Heart::display () const {
    root->display();
}