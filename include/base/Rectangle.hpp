#ifndef __Rect__
#define __Rect__

#include "base/Point.hpp"
#include <GL/glut.h>
#include <GL/gl.h>

class Rectangle {
public:
    Rectangle (const GLfloat _width, const GLfloat _height);
    Rectangle (const Point p, const GLfloat _width, const GLfloat _height);
    Rectangle (const GLfloat _x, const GLfloat _y, const GLfloat _width, const GLfloat _height);
    Point getLeftTop ();
    Point getRightBottom ();
    void setPosition (const GLfloat _x, const GLfloat _y);
    void display (const GLfloat R, const GLfloat G, const GLfloat B);
    
protected:
    GLfloat x; // center
    GLfloat y; // center
    GLfloat width;
    GLfloat height;
};

#endif