#include "entity/Item.hpp"

Item::Item () {
    root->init(RECT);
    root->addChild(TRIANGLE);
    root->addChild(TRIANGLE);
}

Item::~Item () { }

void Item::init (const GLfloat length, const ModelViewMat2D& mat, const Rgba color, const GLfloat speed) {
    Rect* base = (Rect*)**root;
    std::list<FigureNode*> triangles = root->getChildren();
    Triangle* top = (Triangle*)**(triangles.front());
    Triangle* bottom = (Triangle*)**(triangles.back());
    
    base->setMatrix(mat);
    GLfloat radius = length / 2.0f;
    top->setRadius(radius);
    bottom->setRadius(radius);
    top->setTranslate(0.0f, radius / 2.0f);
    bottom->setTranslate(0.0f, -(radius / 2.0f));
    top->rotate(330);
    bottom->rotate(150);
    top->setColor(color);
    bottom->setColor(color);
    setSpeed(speed);
}

void Item::display () const {
    root->display();
}