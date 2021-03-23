#ifndef __BULLET__
#define __BULLET__

#include "3rdobjects/ThirdObject.hpp"
#include "base/Circle.hpp"
#include <iostream>

class Bullet : public ThirdObject {
public:
    void init (const GLfloat radius, const ModelViewMat2D& mat, const Rgba color, const GLfloat speed);
    void display ();

private:
    Circle shape;
};
#endif