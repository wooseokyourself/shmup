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
            return mat.tx < -1.0f;
        case UP:
            return mat.ty > 1.0f;
        case RIGHT:
            return mat.tx > 1.0f;
        case DOWN:
            return mat.ty < -1.0f;
        case LEFT_UP:
            return mat.tx < -1.0f || mat.ty > 1.0f;
        case UP_RIGHT:
            return mat.ty > 1.0f || mat.tx > 1.0f;
        case RIGHT_DOWN:
            return mat.tx > 1.0f || mat.ty < -1.0f;
        case DOWN_LEFT:
            return mat.ty < -1.0f || mat.tx < -1.0f;
    }
}