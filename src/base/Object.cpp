#include "base/Object.hpp"

Object::Object ()
: color(1.0f, 1.0f, 1.0f), speed(0.0f), direction(NONE) {
    mat.setScale(1.0f, 1.0f);
}

/**
 * @param p The center point axis of the object in world space. (each are -1.0 to 1.0)
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 */
Object::Object (const Point2D p)
: color(1.0f, 1.0f, 1.0f), speed(0.0f), direction(NONE) {
    mat.setTranslate(p.x, p.y);
    mat.setScale(1.0f, 1.0f);
}

/**
 * @param x The x value of the center point of the object in world space. (-1.0 to 1.0)
 * @param y The y value of the center point of the object in world space. (-1.0 to 1.0)
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 */
Object::Object (const GLfloat x, const GLfloat y)
: color(1.0f, 1.0f, 1.0f), speed(0.0f), direction(NONE) {
    mat.setTranslate(x, y);
    mat.setScale(1.0f, 1.0f);
}

Point2D Object::getWorldPosition () const {
    return Point2D(mat.tx, mat.ty);
}

/**
 * @brief Set the x and y of the object.
 * @param p New point of the center point of the object in world space.
 */
void Object::setPosition (const Point2D p) {
    mat.setTranslate(p.x, p.y);
}

/**
 * @brief Set the x and y of the object.
 * @param x New x value of the center point of the object in world space.
 * @param y New y value of the center point of the object in world space.
 */
void Object::setPosition (const GLfloat x, const GLfloat y) {
    mat.setTranslate(x, y);
}

/**
 * @brief Set color of the object.
 * @param R The R value of the object's color. (0.0 to 1.0)
 * @param G The G value of the object's color. (0.0 to 1.0)
 * @param B The B value of the object's color. (0.0 to 1.0)
 */
void Object::setColor (const GLfloat _R, const GLfloat _G, const GLfloat _B) {
    color.R = _R;
    color.G = _G;
    color.B = _B;
}

/**
 * @brief Set color of the object.
 * @param color The 3-tuple of RGBA value of the object's color. (each value is 0.0 to 1.0)
 */
void Object::setColor (const Rgba _color) {
    color = _color;    
}

/**
 * @brief Set random color of the object.
 */
void Object::setRandomColor () {
    color = Rgba(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
                static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
                static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

void Object::setSpeed (const GLfloat _speed) {
    speed = _speed;
}

/**
 * @brief Change the position of the object by @speed attribute.
 * @param direction The target direction of the movement; LEFT, RIGHT, UP, DOWN, LEFT_UP, UP_RIGHT, RIGHT_DOWN, DOWN_LEFT
 */
void Object::move (const int direction) {
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