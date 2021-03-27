#ifndef __THIRDOBJECT__
#define __THIRDOBJECT__

#include "base/core/Figure.hpp"
#include "base/core/Circle.hpp"
#include "base/Object.hpp"

class ThirdObject : public Object {
public:
    bool isOutOfBound (const int bound);
    bool isIn (const Point2D leftTop, const Point2D rightBottom);

public:
    virtual void init (const GLfloat radius, const ModelViewMat2D& mat, const Rgba color, const GLfloat speed) = 0;
    virtual void display () = 0;
};

#endif