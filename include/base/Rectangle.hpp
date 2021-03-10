#ifndef __Rect__
#define __Rect__

#include "base/Point.hpp"
#include "base/Rgb.hpp"
#include <GL/glut.h>
#include <GL/gl.h>

class Rectangle {
public:
    Rectangle (const GLfloat _width, const GLfloat _height);
    Rectangle (const Point p, const GLfloat _width, const GLfloat _height);
    Rectangle (const GLfloat _x, const GLfloat _y, const GLfloat _width, const GLfloat _height);
    Point getLeftTop () const;
    Point getRightBottom () const;
    void setPosition (const GLfloat _x, const GLfloat _y);
    void display (const GLfloat R, const GLfloat G, const GLfloat B) const;
    void display (const Rgb color) const;
    
protected:
    GLfloat x; // center
    GLfloat y; // center
    GLfloat width;
    GLfloat height;
};

#endif