#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "base/core/Figure.hpp"

class Triangle : public Figure {
public:
    Triangle () : Figure(), radius(0.0f) { }
    inline void setRadius (const GLfloat _radius) { radius = _radius; }
    inline GLfloat getRadius () const { return radius; }

public:
    inline virtual void draw () const {
        int factor = 3;
        glBegin(GL_POLYGON);
        for (int i = 0 ; i < factor ; i ++)   {
            float degree = 2.0f * 3.1415926f * float(i) / float(factor);
            float x = radius * cosf(degree);
            float y = radius * sinf(degree);
            glVertex2f(x, y);
        }
        glEnd();
        glBegin(GL_LINE_LOOP);
        for (int i = 0 ; i < factor ; i ++)   {
            float degree = 2.0f * 3.1415926f * float(i) / float(factor);
            float x = radius * cosf(degree);
            float y = radius * sinf(degree);
            glVertex2f(x, y);
        }
        glEnd();
    }

protected:
    GLfloat radius;
};

#endif