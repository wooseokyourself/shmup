#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "base/Object.hpp"

class Triangle : public Object {
public:
    Triangle ();
    void setRadius (const GLfloat _radius);

public:
    void display ();

protected:
    GLfloat radius;
};

#endif