#ifndef __BASERECT__
#define __BASERECT__

#include "base/core/Figure.hpp"

class BaseRect : public Figure {
public:
    BaseRect () : Figure(), width(0.0f), height(0.0f) { }
    inline void setSide (const GLfloat _width, const GLfloat _height) {
        width = _width;
        height = _height;
    }
    inline GLfloat getWidth () const { return width; }
    inline GLfloat getHeight () const { return height; }

public: 
    inline virtual void draw () const  {
        GLfloat halfWidth = width / 2;
        glBegin(GL_POLYGON);
            glVertex2f(-halfWidth, height); 
            glVertex2f(-halfWidth, 0.0f);
            glVertex2f(halfWidth, 0.0f);
            glVertex2f(halfWidth, height);
        glEnd();
        glBegin(GL_LINE_LOOP);
            glVertex2f(-halfWidth, height); 
            glVertex2f(-halfWidth, 0.0f);
            glVertex2f(halfWidth, 0.0f);
            glVertex2f(halfWidth, height);
        glEnd();
    }

protected:
    GLfloat width;
    GLfloat height;
};

#endif