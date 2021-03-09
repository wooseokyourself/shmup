#include "DynamicObject/Bullet.hpp"

Bullet::Bullet (const Point p, const GLfloat _width, const GLfloat _height, const GLfloat _speed)
: DynamicObject(p, _width, _height, _speed) {

}

Bullet::Bullet (const GLfloat _width, const GLfloat _height, const GLfloat _speed) 
: DynamicObject(_width, _height, _speed) {
    
}