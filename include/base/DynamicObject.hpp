#ifndef __DYNAMICOBJECT__
#define __DYNAMICOBJECT__

#include "base/Rectangle.hpp"
#include "gameplay/Constants.hpp"

class DynamicObject : public Rectangle {
public:
    DynamicObject (const GLfloat _width, const GLfloat _height, const GLfloat _speed);
    DynamicObject (const Point2D p, const GLfloat _width, const GLfloat _height, const GLfloat _speed);
    DynamicObject (const GLfloat _x, const GLfloat _y, const GLfloat _width, const GLfloat _height, const GLfloat _speed);
    void move (const int direction);

protected:
    GLfloat speed;
    uint8_t direction;
};

#endif