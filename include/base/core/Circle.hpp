#ifndef __CIRCLE__
#define __CIRCLE__

#include "base/core/Figure.hpp"

class Circle : public Figure {
public:
    Circle ();
    void setRadius (const GLfloat _radius);

public:
    void draw () const;

protected:
    GLfloat radius;
};

#endif