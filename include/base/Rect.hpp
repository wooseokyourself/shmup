#ifndef __RECT__
#define __RECT__

#include "base/Object.hpp"

class Rect : public Object {
public:
    Rect(const GLfloat _width, const GLfloat _height);
    Rect(const Point2D p, const GLfloat _width, const GLfloat _height);
    Rect(const GLfloat x, const GLfloat y, const GLfloat _width, const GLfloat _height);
    Point2D getLeftTop() const;
    Point2D getRightBottom() const;

public: 
    void display() const;

protected:
    GLfloat width;
    GLfloat height;
};

#endif