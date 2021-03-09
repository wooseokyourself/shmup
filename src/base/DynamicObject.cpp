#include "base/DynamicObject.hpp"

DynamicObject::DynamicObject (const GLfloat _width, const GLfloat _height, const GLfloat _speed)
: Rectangle(0.0f, 0.0f, _width, _height), speed(_speed), direction(NONE), nextForward(0.0f) {

}

DynamicObject::DynamicObject (const Point p, const GLfloat _width, const GLfloat _height, const GLfloat _speed)
: Rectangle(p, _width, _height), speed(_speed), direction(NONE), nextForward(0.0f) {

}

DynamicObject::DynamicObject (const GLfloat _x, const GLfloat _y, const GLfloat _width, const GLfloat _height, const GLfloat _speed)
: Rectangle(_x, _y, _width, _height), speed(_speed), direction(NONE), nextForward(0.0f) {

}

void DynamicObject::move (const int direction) {
    switch (direction) {
        case NONE:
            break;
        case LEFT:
            if (x > -1)
                x -= speed;
            break;
        case RIGHT:
            if (x < 1)
                x += speed;
            break;
        case UP:
            if (y < 1)
                y += speed;
            break;
        case DOWN:
            if (y > -1)
                y -= speed;
            break;
        case LEFT_UP:
            if (x > -1)
                x -= speed / (GLfloat)1.41421;;
            if (y < 1)
                y += speed / (GLfloat)1.41421;;
            break;
        case UP_RIGHT:
            if (y < 1)
                y += speed / (GLfloat)1.41421;;
            if (x < 1)
                x += speed / (GLfloat)1.41421;;
            break;
        case RIGHT_DOWN:
            if (x < 1)
                x += speed / (GLfloat)1.41421;;
            if (y > -1)
                y -= speed / (GLfloat)1.41421;;
            break;
        case DOWN_LEFT:
            if (y > -1)
                y -= speed / (GLfloat)1.41421;;
            if (x > -1)
                x -= speed / (GLfloat)1.41421;;
            break;
    }
}