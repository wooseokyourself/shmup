#ifndef __RECT__
#define __RECT__

#include "base/core/Figure.hpp"

class Rect : public Figure {
public:
    Rect () : Figure(), width(0.0f), height(0.0f) { }
    inline void setSide (const GLfloat _width, const GLfloat _height) {
        width = _width; height = _height;
    }
    inline GLfloat getWidth () const { return width; }
    inline GLfloat getHeight () const { return height; }

public:
    inline virtual void draw () const {
        GLfloat w = width / 2;
        GLfloat h = height / 2;
        glBegin(GL_POLYGON);
            glVertex2f(-w, -h); 
            glVertex2f(-w, h);
            glVertex2f(w, h);
            glVertex2f(w, -h);
        glEnd();
        glBegin(GL_LINE_LOOP);
            glVertex2f(-w, -h); 
            glVertex2f(-w, h);
            glVertex2f(w, h);
            glVertex2f(w, -h);
        glEnd();
    }

protected:
    GLfloat width;
    GLfloat height;
};

#endif