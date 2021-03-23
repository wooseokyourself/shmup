#ifndef __CIRCLE__
#define __CIRCLE__

#include "base/Object.hpp"

class Circle : public Object {
public:
    Circle ();
    void setRadius (const GLfloat _radius);

public:
    void display ();

protected:
    GLfloat radius;
};

#endif