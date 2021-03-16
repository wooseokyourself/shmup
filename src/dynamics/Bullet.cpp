#include "dynamics/Bullet.hpp"

Bullet::Bullet (const Point2D p, const GLfloat _width, const GLfloat _height, const GLfloat _speed)
: DynamicObject(p, _width, _height, _speed) { }

Bullet::Bullet (const GLfloat _width, const GLfloat _height, const GLfloat _speed) 
: DynamicObject(_width, _height, _speed) { }

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