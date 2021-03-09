#include "DynamicObject/DynamicObject.hpp"

DynamicObject::DynamicObject (const GLfloat _width, const GLfloat _height, const GLfloat _speed)
: x(0), y(0), width(_width), height(_height), speed(_speed) {

}

DynamicObject::DynamicObject (const Point p, const GLfloat _width, const GLfloat _height, const GLfloat _speed)
: x(p.x), y(p.y), width(_width), height(_height), speed(_speed) {

}

DynamicObject::DynamicObject (const GLfloat _x, const GLfloat _y, const GLfloat _width, const GLfloat _height, const GLfloat _speed)
: x(_x), y(_y), width(_width), height(_height), speed(_speed) {

}

Point DynamicObject::getLeftTop () {
    GLfloat halfWidth = width / 2;
    GLfloat halfHeight = height / 2;
    return Point(x - halfWidth, y + halfHeight);
}

Point DynamicObject::getRightBottom () {
    GLfloat halfWidth = width / 2;
    GLfloat halfHeight = height / 2;
    return Point(x + halfWidth, y - halfHeight);
}

void DynamicObject::setPosition (const GLfloat _x, const GLfloat _y) {
    this->x = _x;
    this->y = _y;
}

void DynamicObject::moveLeft () { this->x -= this->speed; }

void DynamicObject::moveRight () { this->x += this->speed; }

void DynamicObject::moveUp () { this->y += this->speed; }

void DynamicObject::moveDown () { this->y -= this->speed; }

void DynamicObject::display (const GLfloat R, const GLfloat G, const GLfloat B) {
    glColor3f(R, G, B);
    GLfloat w = this->width / 2;
    GLfloat h = this->height / 2;
    glBegin(GL_LINE_LOOP);
        glVertex2f(this->x - w, this->y - h); 
        glVertex2f(this->x - w, this->y + h);
        glVertex2f(this->x + w, this->y + h);
        glVertex2f(this->x + w, this->y - h);
    glEnd();
    glutPostRedisplay(); // ?
}

bool DynamicObject::isOutOfBound () {
    return x < -1.0f || x > 1.0f || y < -1.0f || y > 1.0f;
}