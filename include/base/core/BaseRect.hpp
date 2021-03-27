#ifndef __BASERECT__
#define __BASERECT__

#include "base/core/Figure.hpp"

class BaseRect : public Figure {
public:
    BaseRect ();
    void setSide (const GLfloat _width, const GLfloat _height);
    Point2D getLeftTop () const;
    Point2D getRightBottom () const;

public: 
    void draw () const;

protected:
    GLfloat width;
    GLfloat height;
};

#endif