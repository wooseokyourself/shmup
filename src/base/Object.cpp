#include "base/Object.hpp"

Object::Object ()
: speed(0.0f) {
    root = new FigureNode;
}

Object::~Object () {
    if (root != nullptr)
        delete root;
}

void Object::setSpeed (const GLfloat _speed) {
    speed = _speed;
}

/**
 * @return true if the center of object is in rectangle.
 * @param leftTop The left-top point of the target range in world space.
 * @param rightBottom The right-bottom point of the target range in world space.
 */
bool Object::isIn (const Point2D leftTop, const Point2D rightBottom) const {
    Point2D p = (**root)->getWorldPosition();
    if ( (leftTop.x <= p.x && p.x <= rightBottom.x) && (rightBottom.y <= p.y && p.y <= leftTop.y))
        return true;
}

void Object::move (const GLfloat degree) {
    const ModelViewMat2D& mat = (**root)->getMatrix();
    GLfloat rad = getRadian(mat.degree + degree);
    GLfloat x = speed * cos(rad);
    GLfloat y = speed * sin(rad);
    (**root)->translate(x, y);
    handlingWhenOutOfBound();
}

void Object::rotate (const GLfloat degree) {
    (**root)->rotate(degree);
}

/**
 * @return true if the object is out of bound.
 */
bool Object::isCenterOutOfBound () const {
    const Point2D pos = (**root)->getWorldPosition();
    const GLfloat x = pos.x;
    const GLfloat y = pos.y;
    return x < WORLD_BOUND::LEFT || x > WORLD_BOUND::RIGHT || y < WORLD_BOUND::DOWN || y > WORLD_BOUND::UP;
}