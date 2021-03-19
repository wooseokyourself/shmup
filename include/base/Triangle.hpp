#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "base/Object.hpp"

class Triangle : public Object {
public:
    Triangle (const GLfloat _radius);
    Triangle (const Point2D p, const GLfloat _radius);
    Triangle (const GLfloat x, const GLfloat y, const GLfloat _radius);

public:
    void display () const;

protected:
    GLfloat radius;
};

#endif