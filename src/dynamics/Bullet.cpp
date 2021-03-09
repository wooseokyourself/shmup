#include "dynamics/Bullet.hpp"

Bullet::Bullet (const Point p, const GLfloat _width, const GLfloat _height, const GLfloat _speed)
: DynamicObject(p, _width, _height, _speed) {

}

Bullet::Bullet (const GLfloat _width, const GLfloat _height, const GLfloat _speed) 
: DynamicObject(_width, _height, _speed) {
    
}

bool Bullet::isOutOfBound (const int bound) {
    switch (bound) {
        case LEFT:
            return x < -1.0f;
        case UP:
            return y > 1.0f;
        case RIGHT:
            return x > 1.0f;
        case DOWN:
            return y < -1.0f;
        case LEFT_UP:
            return x < -1.0f || y > 1.0f;
        case UP_RIGHT:
            return y > 1.0f || x > 1.0f;
        case RIGHT_DOWN:
            return x > 1.0f || y < -1.0f;
        case DOWN_LEFT:
            return y < -1.0f || x < -1.0f;
    }
}