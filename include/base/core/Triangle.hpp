#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "base/core/Figure.hpp"

class Triangle : public Figure {
public:
    Triangle ();
    void setRadius (const GLfloat _radius);

public:
    void draw () const;

protected:
    GLfloat radius;
};

#endif