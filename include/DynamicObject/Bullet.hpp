#ifndef __BULLET__
#define __BULLET__

#include "DynamicObject/DynamicObject.hpp"

class Bullet : public DynamicObject {
public:
    Bullet (const Point p, const GLfloat _width, const GLfloat _height, const GLfloat _speed);
    Bullet (const GLfloat _width, const GLfloat _height, const GLfloat _speed);
};

#endif