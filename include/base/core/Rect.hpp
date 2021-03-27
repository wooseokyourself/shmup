#ifndef __RECT__
#define __RECT__

#include "base/core/Figure.hpp"

class Rect : public Figure {
public:
    Rect ();
    void setSide (const GLfloat _width, const GLfloat _height);
    Point2D getLeftTop () const;
    Point2D getRightBottom () const;

public: 
    // void display ();
    void draw () const;

protected:
    GLfloat width;
    GLfloat height;
};

#endif