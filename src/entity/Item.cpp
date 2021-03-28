#include "entity/Item.hpp"

Item::Item ()
: base(nullptr), activatedTime(0.0f) {
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

bool Item::isDurationTimeout () const {
    if (glutGet(GLUT_ELAPSED_TIME) - activatedTime >= ITEM_DURATION_SECS * 1000.0f) 
        return true;
    return false;
}

void Item::handlingWhenOutOfBound () {
    const ModelViewMat2D mat = base->getMatrix();
    const GLfloat x = base->getMatrix().tx, y = base->getMatrix().ty;
    bool outOfBound = false;
    GLfloat minDegree = mat.degree, maxDegree = mat.degree;
    if (mat.tx < WORLD_BOUND::LEFT) { // 총알이 0 ~ 180 
        base->setTranslate(WORLD_BOUND::LEFT, mat.ty);
        if (mat.degree < 90.0f)
            minDegree = 270.0f, maxDegree = 360.0f;
        else if (mat.degree > 90.0f)
            minDegree = 180.0f, maxDegree = 270.0f;
        else
            minDegree = 180.0f, maxDegree = 360.0f;
    }
    else if (mat.tx > WORLD_BOUND::RIGHT) {
        base->setTranslate(WORLD_BOUND::RIGHT, mat.ty);
        if (mat.degree < 270.0f)
            minDegree = 0.0f, maxDegree = 90.0f;
        else if (mat.degree > 270.0f)
            minDegree = 90.0f, maxDegree = 180.0f;
        else
            minDegree = 0.0f, maxDegree = 180.0f;
    }
    if (mat.ty > WORLD_BOUND::UP) {
        base->setTranslate(mat.tx, WORLD_BOUND::UP);
        if (mat.degree < 90.0f)
            minDegree = 90.0f, maxDegree = 180.0f;
        else if (mat.degree > 270.0f)
            minDegree = 180.0f, maxDegree = 270.0f;
        else
            minDegree = 90.0f, maxDegree = 270.0f;
    }
    else if (mat.ty < WORLD_BOUND::DOWN) {
        base->setTranslate(mat.tx, WORLD_BOUND::DOWN);
        if (mat.degree < 180.0f)
            minDegree = 0.0f, maxDegree = 90.0f;
        else if (mat.degree > 180.0f)
            minDegree = 270.0f, maxDegree = 360.0f;
        else
            minDegree = 270.0f, maxDegree = 450.0f;
    }
    base->setRotate(randomRealNumber(minDegree, maxDegree));
}

void Item::display () const {
    root->display();
}