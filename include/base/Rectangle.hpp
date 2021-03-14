#ifndef __Rect__
#define __Rect__

#include "base/Point2D.hpp"
#include "base/Rgb.hpp"
#include <cstdlib>
#include <GL/glut.h>
#include <GL/gl.h>

class Rectangle {
public:
    Rectangle (const GLfloat _width, const GLfloat _height);
    Rectangle (const Point2D p, const GLfloat _width, const GLfloat _height);
    Rectangle (const GLfloat _x, const GLfloat _y, const GLfloat _width, const GLfloat _height);
    Point2D getLeftTop () const;
    Point2D getRightBottom () const;
    void setPosition (const GLfloat _x, const GLfloat _y);
    void display () const;
    void setColor (const GLfloat _R, const GLfloat _G, const GLfloat _B);
    void setColor (const Rgb _color);
    void setRandomColor ();
    
protected:
    GLfloat x; // center
    GLfloat y; // center
    GLfloat width;
    GLfloat height;
    Rgb color;
};

#endif