#include "base/Object.hpp"

Object::Object ()
: root(nullptr), speed(0) { }

Object::~Object () {
    if (root != nullptr)
        delete root;
}

void Object::setSpeed (const GLfloat _speed) {
    speed = _speed;
}

/**
 * @brief Change the position of the object by @speed attribute.
 * @param direction The target direction of the movement; LEFT, RIGHT, UP, DOWN, LEFT_UP, UP_RIGHT, RIGHT_DOWN, DOWN_LEFT
 */
void Object::move (const int direction) {
    const Point2D pos = (**root)->getWorldPosition();
    const GLfloat x = pos.x;
    const GLfloat y = pos.y;
    switch (direction) {
        case NONE:
            break;
        case LEFT:
            if (x > WORLD_BOUND::LEFT)
                (**root)->translate(-speed, 0.0f);
            break;
        case RIGHT:
            if (x < WORLD_BOUND::RIGHT)
                (**root)->translate(speed, 0.0f);
            break;
        case UP:
            if (y < WORLD_BOUND::UP)
                (**root)->translate(0.0f, speed);
            break;
        case DOWN:
            if (y > WORLD_BOUND::DOWN)
                (**root)->translate(0.0f, -speed);
            break;
        case LEFT_UP:
            if (x > WORLD_BOUND::LEFT)
                (**root)->translate(-(speed/(GLfloat)1.41421), 0.0f);
            if (y < WORLD_BOUND::UP)
                (**root)->translate(0.0f, (speed/(GLfloat)1.41421));
            break;
        case UP_RIGHT:
            if (y < WORLD_BOUND::UP)
                (**root)->translate(0.0f, (speed/(GLfloat)1.41421));
            if (x < WORLD_BOUND::RIGHT)
                (**root)->translate((speed/(GLfloat)1.41421), 0.0f);
            break;
        case RIGHT_DOWN:
            if (x < WORLD_BOUND::RIGHT)
                (**root)->translate((speed/(GLfloat)1.41421), 0.0f);
            if (y > WORLD_BOUND::DOWN)
                (**root)->translate(0.0f, -(speed/(GLfloat)1.41421));
            break;
        case DOWN_LEFT:
            if (y > WORLD_BOUND::DOWN)
                (**root)->translate(0.0f, -(speed/(GLfloat)1.41421));
            if (x > WORLD_BOUND::LEFT)
                (**root)->translate(-(speed/(GLfloat)1.41421), 0.0f);
            break;
    }
}

void Object::rotate (const GLfloat degree) {
    (**root)->rotate(degree);
}