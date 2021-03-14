#include "base/DynamicObject.hpp"

/**
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 * @param _speed (-1.0 to 1.0)
 */
DynamicObject::DynamicObject (const GLfloat _width, const GLfloat _height, const GLfloat _speed)
: Rectangle(0.0f, 0.0f, _width, _height), speed(_speed), direction(NONE), nextForward(0.0f) { }

/**
 * @param p The center point axis of the object. (each are -1.0 to 1.0)
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 * @param _speed (-1.0 to 1.0)
 */
DynamicObject::DynamicObject (const Point p, const GLfloat _width, const GLfloat _height, const GLfloat _speed)
: Rectangle(p, _width, _height), speed(_speed), direction(NONE), nextForward(0.0f) { }

/**
 * @param _x The x value of the center point of the object. (-1.0 to 1.0)
 * @param _y The y value of the center point of the object. (-1.0 to 1.0)
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 * @param _speed (-1.0 to 1.0)
 */
DynamicObject::DynamicObject (const GLfloat _x, const GLfloat _y, const GLfloat _width, const GLfloat _height, const GLfloat _speed)
: Rectangle(_x, _y, _width, _height), speed(_speed), direction(NONE), nextForward(0.0f) { }

/**
 * @brief Change the position of the object by @speed attribute.
 * @param direction The target direction of the movement; LEFT, RIGHT, UP, DOWN, LEFT_UP, UP_RIGHT, RIGHT_DOWN, DOWN_LEFT
 */
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