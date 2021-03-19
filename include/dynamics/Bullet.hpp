#ifndef __BULLET__
#define __BULLET__

#include "base/Circle.hpp"

class Bullet : public Circle {
public:
    Bullet (const GLfloat _radius, const GLfloat _speed);
    Bullet (const Point2D p, const GLfloat _radius, const GLfloat _speed);
    bool isOutOfBound (const int bound);
    bool isIn (const Point2D leftTop, const Point2D rightBottom);
};

#endif