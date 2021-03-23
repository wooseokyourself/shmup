#ifndef __THIRDOBJECT__
#define __THIRDOBJECT__

#include "base/Object.hpp"
#include "base/Circle.hpp"

class ThirdObject : public Object {
public:
    void setMatrix (const ModelViewMat2D& mat);
    bool isOutOfBound (const int bound);
    bool isIn (const Point2D leftTop, const Point2D rightBottom);

public:
    virtual void init (const GLfloat radius, const ModelViewMat2D& mat, const Rgba color, const GLfloat speed) = 0;
    virtual void display () = 0;
};

#endif