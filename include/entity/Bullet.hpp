#ifndef __BULLET__
#define __BULLET__

#include "base/ThirdObject.hpp"
#include "base/Circle.hpp"
#include <iostream>

class Bullet : public ThirdObject {
public:
    void init (const GLfloat radius, const ModelViewMat2D& mat, const Rgba color, const GLfloat speed);
    void display ();
    void draw () const;

private:
    Circle shape;
};
#endif