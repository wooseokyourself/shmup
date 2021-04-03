#include "entity/Item.hpp"

Item::Item ()
: activatedTime(0.0f) {
    top = pushChild(TRIANGLE, FRONT);
    bottom = pushChild(TRIANGLE, FRONT);
}

void Item::init (const TransformMatrix& mat, const GLfloat length, const Rgba color, const GLfloat speed) {
    setMatrix(mat);
    GLfloat radius = length / 3.0f;
    ((Triangle*)**top)->setRadius(radius);
    ((Triangle*)**bottom)->setRadius(radius);

    top->setTranslate(0.0f, radius / 2.0f);
    top->setRotate(-30.0f);
    top->setColor(color);
    
    bottom->setTranslate(0.0f, -(radius / 2.0f));
    bottom->setRotate(30.0f); 
    bottom->setColor(color);
    
    setSpeed(speed);
    activatedTime = glutGet(GLUT_ELAPSED_TIME);
}

bool Item::isDurationTimeout () const {
    if (glutGet(GLUT_ELAPSED_TIME) - activatedTime >= ITEM_DURATION_SECS * 1000.0f) 
        return true;
    return false;
}

void Item::handlingWhenOutOfBound () {
    const TransformMatrix mat = getModelViewMatrix();
    const GLfloat x = mat.tx, y = mat.ty;
    bool outOfBound = false;
    GLfloat minDegree = mat.degree, maxDegree = mat.degree;
    if (mat.tx < WORLD_BOUND::LEFT) { // 총알이 0 ~ 180 
        setTranslate(WORLD_BOUND::LEFT, mat.ty);
        if (mat.degree < 90.0f)
            minDegree = 270.0f, maxDegree = 360.0f;
        else if (mat.degree > 90.0f)
            minDegree = 180.0f, maxDegree = 270.0f;
        else
            minDegree = 180.0f, maxDegree = 360.0f;
    }
    else if (mat.tx > WORLD_BOUND::RIGHT) {
        setTranslate(WORLD_BOUND::RIGHT, mat.ty);
        if (mat.degree < 270.0f)
            minDegree = 0.0f, maxDegree = 90.0f;
        else if (mat.degree > 270.0f)
            minDegree = 90.0f, maxDegree = 180.0f;
        else
            minDegree = 0.0f, maxDegree = 180.0f;
    }
    if (mat.ty > WORLD_BOUND::UP) {
        setTranslate(mat.tx, WORLD_BOUND::UP);
        if (mat.degree < 90.0f)
            minDegree = 90.0f, maxDegree = 180.0f;
        else if (mat.degree > 270.0f)
            minDegree = 180.0f, maxDegree = 270.0f;
        else
            minDegree = 90.0f, maxDegree = 270.0f;
    }
    else if (mat.ty < WORLD_BOUND::DOWN) {
        setTranslate(mat.tx, WORLD_BOUND::DOWN);
        if (mat.degree < 180.0f)
            minDegree = 0.0f, maxDegree = 90.0f;
        else if (mat.degree > 180.0f)
            minDegree = 270.0f, maxDegree = 360.0f;
        else
            minDegree = 270.0f, maxDegree = 450.0f;
    }
    setRotate(randomRealNumber(minDegree, maxDegree));
}

void Item::update () {
    Object::update();
}

void Item::display () const {
    Object::display();
}