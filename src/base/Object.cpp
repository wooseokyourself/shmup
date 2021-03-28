#include "base/Object.hpp"

Object::Object ()
: speed(0.0f) {
    root = new FigureNode;
}

Object::~Object () {
    if (root != nullptr)
        delete root;
}

void Object::setSpeed (const GLfloat _speed) {
    speed = _speed;
}

/**
 * @return true if the object is out of bound.
 */
bool Object::isOutOfBound () const {
    const Point2D pos = (**root)->getWorldPosition();
    const GLfloat x = pos.x;
    const GLfloat y = pos.y;
    return x < WORLD_BOUND::LEFT || x > WORLD_BOUND::RIGHT || y < WORLD_BOUND::DOWN || y > WORLD_BOUND::UP;
}

/**
 * @return true if the object is out of bound.
 * @param bound The target bound; LEFT, RIGHT, UP, DOWN, LEFT_UP, UP_RIGHT, RIGHT_DOWN, DOWN_LEFT
 */
bool Object::isOutOfBound (const int bound) const {
    const Point2D pos = (**root)->getWorldPosition();
    const GLfloat x = pos.x;
    const GLfloat y = pos.y;
    switch (bound) {
        case LEFT:
            return x < WORLD_BOUND::LEFT;
        case UP:
            return y > WORLD_BOUND::UP;
        case RIGHT:
            return x > WORLD_BOUND::RIGHT;
        case DOWN:
            return y < WORLD_BOUND::DOWN;
        case LEFT_UP:
            return x < WORLD_BOUND::LEFT || y > WORLD_BOUND::UP;
        case UP_RIGHT:
            return y > WORLD_BOUND::UP || x > WORLD_BOUND::RIGHT;
        case RIGHT_DOWN:
            return x > WORLD_BOUND::RIGHT || y < WORLD_BOUND::DOWN;
        case DOWN_LEFT:
            return y < WORLD_BOUND::DOWN || x < WORLD_BOUND::LEFT;
    }
}

/**
 * @return true if the center of object is in rectangle.
 * @param leftTop The left-top point of the target range in world space.
 * @param rightBottom The right-bottom point of the target range in world space.
 */
bool Object::isIn (const Point2D leftTop, const Point2D rightBottom) const {
    Point2D p = (**root)->getWorldPosition();
    if ( (leftTop.x <= p.x && p.x <= rightBottom.x) && (rightBottom.y <= p.y && p.y <= leftTop.y))
        return true;
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