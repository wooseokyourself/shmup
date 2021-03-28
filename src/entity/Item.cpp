#include "entity/Item.hpp"

Item::Item ():
base(nullptr), activatedTime(0.0f) {
    root->init(RECT);
    root->addChild(TRIANGLE);
    root->addChild(TRIANGLE);
}

Item::~Item () { }

void Item::init (const ModelViewMat2D& mat, const GLfloat length, const Rgba color, const GLfloat speed) {
    base = (Rect*)**root;
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
    activatedTime = glutGet(GLUT_ELAPSED_TIME);
}

void Item::setRandomRotate () {
    base->setRotate(randomRealNumber(0.0f, 360.0f));
}

bool Item::shouldBeRemoved () {
    if (glutGet(GLUT_ELAPSED_TIME) - activatedTime >= ITEM_DURATION_SECS * 1000.0f) 
        return true;
    return false;
}

void Item::move () {
    const ModelViewMat2D& mat = (**root)->getMatrix();
    GLfloat rad = getRadian(mat.degree);
    GLfloat x = speed * cos(rad);
    GLfloat y = speed * sin(rad);
    (**root)->translate(x, y);
}

void Item::display () const {
    root->display();
}