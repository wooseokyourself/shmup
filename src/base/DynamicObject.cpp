#include "base/DynamicObject.hpp"

/**
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 * @param _speed (-1.0 to 1.0)
 */
DynamicObject::DynamicObject (const GLfloat _width, const GLfloat _height, const GLfloat _speed)
: Rectangle(0.0f, 0.0f, _width, _height), speed(_speed), direction(NONE) { }

/**
 * @param p The center point axis of the object. (each are -1.0 to 1.0)
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 * @param _speed (-1.0 to 1.0)
 */
DynamicObject::DynamicObject (const Point2D p, const GLfloat _width, const GLfloat _height, const GLfloat _speed)
: Rectangle(p, _width, _height), speed(_speed), direction(NONE) { }

/**
 * @param _x The x value of the center point of the object. (-1.0 to 1.0)
 * @param _y The y value of the center point of the object. (-1.0 to 1.0)
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 * @param _speed (-1.0 to 1.0)
 */
DynamicObject::DynamicObject (const GLfloat _x, const GLfloat _y, const GLfloat _width, const GLfloat _height, const GLfloat _speed)
: Rectangle(_x, _y, _width, _height), speed(_speed), direction(NONE) { }

/**
 * @brief Change the position of the object by @speed attribute.
 * @param direction The target direction of the movement; LEFT, RIGHT, UP, DOWN, LEFT_UP, UP_RIGHT, RIGHT_DOWN, DOWN_LEFT
 */
void DynamicObject::move (const int direction) {
    switch (direction) {
        case NONE:
            break;
        case LEFT:
            if (mat.tx > WORLD_BOUND::LEFT)
                mat.moveTranslate(-speed, 0.0f);
            break;
        case RIGHT:
            if (mat.tx < WORLD_BOUND::RIGHT)
                mat.moveTranslate(speed, 0.0f);
            break;
        case UP:
            if (mat.ty < WORLD_BOUND::UP)
                mat.moveTranslate(0.0f, speed);
            break;
        case DOWN:
            if (mat.ty > WORLD_BOUND::DOWN)
                mat.moveTranslate(0.0f, -speed);
            break;
        case LEFT_UP:
            if (mat.tx > WORLD_BOUND::LEFT)
                mat.moveTranslate(-(speed/(GLfloat)1.41421), 0.0f);
            if (mat.ty < WORLD_BOUND::UP)
                mat.moveTranslate(0.0f, (speed/(GLfloat)1.41421));
            break;
        case UP_RIGHT:
            if (mat.ty < WORLD_BOUND::UP)
                mat.moveTranslate(0.0f, (speed/(GLfloat)1.41421));
            if (mat.tx < WORLD_BOUND::RIGHT)
                mat.moveTranslate((speed/(GLfloat)1.41421), 0.0f);
            break;
        case RIGHT_DOWN:
            if (mat.tx < WORLD_BOUND::RIGHT)
                mat.moveTranslate((speed/(GLfloat)1.41421), 0.0f);
            if (mat.ty > WORLD_BOUND::DOWN)
                mat.moveTranslate(0.0f, -(speed/(GLfloat)1.41421));
            break;
        case DOWN_LEFT:
            if (mat.ty > WORLD_BOUND::DOWN)
                mat.moveTranslate(0.0f, -(speed/(GLfloat)1.41421));
            if (mat.tx > WORLD_BOUND::LEFT)
                mat.moveTranslate(-(speed/(GLfloat)1.41421), 0.0f);
            break;
    }
}