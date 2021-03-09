#ifndef __BULLET__
#define __BULLET__

#include "base/DynamicObject.hpp"

class Bullet : public DynamicObject {
public:
    Bullet (const Point p, const GLfloat _width, const GLfloat _height, const GLfloat _speed);
    Bullet (const GLfloat _width, const GLfloat _height, const GLfloat _speed);
    bool isOutOfBound (const int bound);
};

#endif