#ifndef __RECT__
#define __RECT__

#include "base/Object.hpp"

class Rect : public Object {
public:
    Rect ();
    void setSide (const GLfloat _width, const GLfloat _height);
    Point2D getLeftTop () const;
    Point2D getRightBottom () const;

public: 
    void display ();

protected:
    GLfloat width;
    GLfloat height;
};

#endif