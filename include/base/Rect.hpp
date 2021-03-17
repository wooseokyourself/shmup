#ifndef __RECT__
#define __RECT__

#include "base/Point2D.hpp"
#include "base/Rgb.hpp"
#include "base/ModelViewMat2D.hpp"
#include <cstdlib>
#include <GL/glut.h>
#include <GL/gl.h>

class Rect {
public:
    Rect(const GLfloat _width, const GLfloat _height);
    Rect(const Point2D p, const GLfloat _width, const GLfloat _height);
    Rect(const GLfloat x, const GLfloat y, const GLfloat _width, const GLfloat _height);
    Point2D getLeftTop() const;
    Point2D getRightBottom() const;
    void setPosition(const GLfloat x, const GLfloat y);
    void display() const;
    void setColor(const GLfloat _R, const GLfloat _G, const GLfloat _B);
    void setColor(const Rgb _color);
    void setRandomColor();

protected:
    GLfloat width;
    GLfloat height;
    Rgb color;
    ModelViewMat2D mat;
};

#endif