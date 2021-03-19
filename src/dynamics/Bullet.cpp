#include "dynamics/Bullet.hpp"

Bullet::Bullet (const GLfloat _radius, const GLfloat _speed) 
: Circle(_radius) {
    setSpeed(_speed);
}

Bullet::Bullet (const Point2D p, const GLfloat _radius, const GLfloat _speed)
: Circle(p, _radius) {
    setSpeed(_speed);
}

/**
 * @return true if the bullet is out of bound.
 * @param bound The target bound; LEFT, RIGHT, UP, DOWN, LEFT_UP, UP_RIGHT, RIGHT_DOWN, DOWN_LEFT
 */
bool Bullet::isOutOfBound (const int bound) {
    switch (bound) {
        case LEFT:
            return mat.tx < WORLD_BOUND::LEFT;
        case UP:
            return mat.ty > WORLD_BOUND::UP;
        case RIGHT:
            return mat.tx > WORLD_BOUND::RIGHT;
        case DOWN:
            return mat.ty < WORLD_BOUND::DOWN;
        case LEFT_UP:
            return mat.tx < WORLD_BOUND::LEFT || mat.ty > WORLD_BOUND::UP;
        case UP_RIGHT:
            return mat.ty > WORLD_BOUND::UP || mat.tx > WORLD_BOUND::RIGHT;
        case RIGHT_DOWN:
            return mat.tx > WORLD_BOUND::RIGHT || mat.ty < WORLD_BOUND::DOWN;
        case DOWN_LEFT:
            return mat.ty < WORLD_BOUND::DOWN || mat.tx < WORLD_BOUND::LEFT;
    }
}

/**
 * @return true if the bullet is in rectangle.
 * @param leftTop The left-top point of the target range in world space.
 * @param rightBottom The right-bottom point of the target range in world space.
 */
bool Bullet::isIn (const Point2D leftTop, const Point2D rightBottom) {
    Point2D p = getWorldPosition();
    if ( (leftTop.x <= p.x && p.x <= rightBottom.x) && (rightBottom.y <= p.y && p.y <= leftTop.y))
        return true;
}