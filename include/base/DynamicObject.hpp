#ifndef __DYNAMICOBJECT__
#define __DYNAMICOBJECT__

#include "base/Rectangle.hpp"

enum Direction {
    NONE        = 0,
    LEFT        = 0x0064,
    UP          = 0x0065,
    RIGHT       = 0x0066,
    DOWN        = 0x0067,
    LEFT_UP     = 1,
    UP_RIGHT    = 2,
    RIGHT_DOWN  = 3,
    DOWN_LEFT   = 4
};

class DynamicObject : public Rectangle {
public:
    DynamicObject (const GLfloat _width, const GLfloat _height, const GLfloat _speed);
    DynamicObject (const Point p, const GLfloat _width, const GLfloat _height, const GLfloat _speed);
    DynamicObject (const GLfloat _x, const GLfloat _y, const GLfloat _width, const GLfloat _height, const GLfloat _speed);
    void move (const int direction);

protected:
    GLfloat speed;
    uint8_t direction;
    GLfloat nextForward;
};

#endif