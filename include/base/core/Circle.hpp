#ifndef __CIRCLE__
#define __CIRCLE__

#include "base/core/Figure.hpp"

class Circle : public Figure {
public:
    Circle () : Figure(), radius(0.0f) { }
    inline void setRadius (const GLfloat _radius) { radius = _radius; }
    inline GLfloat getRadius () const { return radius; }

public:
    inline virtual void draw () const {
        // draw refer: https://stackoverflow.com/questions/22444450/drawing-circle-with-opengl
        int segment = 30;
        glBegin(GL_POLYGON);
        for (int i = 0 ; i < segment ; i ++)   {
            float degree = 2.0f * 3.1415926f * float(i) / float(segment);//get the current angle 
            float x = radius * cosf(degree);//calculate the x component 
            float y = radius * sinf(degree);//calculate the y component 
            glVertex2f(x, y);
        }
        glEnd();
        glBegin(GL_LINE_LOOP);
        for (int i = 0 ; i < segment ; i ++)   {
            float degree = 2.0f * 3.1415926f * float(i) / float(segment);//get the current angle 
            float x = radius * cosf(degree);//calculate the x component 
            float y = radius * sinf(degree);//calculate the y component 
            glVertex2f(x, y);
        }
        glEnd();
    }

protected:
    GLfloat radius;
};

#endif