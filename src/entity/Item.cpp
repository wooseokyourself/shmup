#include "entity/Item.hpp"

Item::Item () {
    root->init(RECT);
    root->addChild(TRIANGLE);
    root->addChild(TRIANGLE);
}

Item::~Item () { }

void Item::init (const ModelViewMat2D& mat, const GLfloat length, const Rgba color, const GLfloat speed) {
    Rect* base = (Rect*)**root;
    std::list<FigureNode*> triangles = root->getChildren();
    Triangle* top = (Triangle*)**(triangles.front());
    Triangle* bottom = (Triangle*)**(triangles.back());
    
    base->setMatrix(mat);
    GLfloat radius = length / 3.0f;
    top->clearMatrix();
    top->setRadius(radius);
    top->setTranslate(0.0f, radius / 2.0f);
    top->setRotate(-30.0f);
    top->setColor(color);
    
    bottom->clearMatrix();
    bottom->setRadius(radius);
    bottom->setTranslate(0.0f, -(radius / 2.0f));
    bottom->setRotate(30.0f); 
    bottom->setColor(color);
    
    setSpeed(speed);
}

void Item::move () {
    (**root)->translate(0.0f, speed);
}

void Item::display () const {
    root->display();
}