#ifndef __CIRCLE__
#define __CIRCLE__

#include "base/Object.hpp"

class Circle : public Object {
public:
    Circle (const GLfloat _radius);
    Circle (const Point2D p, const GLfloat _radius);
    Circle (const GLfloat x, const GLfloat y, const GLfloat _radius);

public:
    void display () const;

protected:
    GLfloat radius;
};

#endif