#include "base/Rectangle.hpp"

Rectangle::Rectangle (const GLfloat _width, const GLfloat _height)
: x(0), y(0), width(_width), height(_height) {

}

Rectangle::Rectangle (const Point p, const GLfloat _width, const GLfloat _height)
: x(p.x), y(p.y), width(_width), height(_height) {

}

Rectangle::Rectangle (const GLfloat _x, const GLfloat _y, const GLfloat _width, const GLfloat _height)
: x(_x), y(_y), width(_width), height(_height) {

}

Point Rectangle::getLeftTop () {
    GLfloat halfWidth = width / 2;
    GLfloat halfHeight = height / 2;
    return Point(x - halfWidth, y + halfHeight);
}

Point Rectangle::getRightBottom () {
    GLfloat halfWidth = width / 2;
    GLfloat halfHeight = height / 2;
    return Point(x + halfWidth, y - halfHeight);
}

void Rectangle::setPosition (const GLfloat _x, const GLfloat _y) {
    x = _x;
    y = _y;
}

void Rectangle::display (const GLfloat R, const GLfloat G, const GLfloat B) {
    glColor3f(R, G, B);
    GLfloat w = width / 2;
    GLfloat h = height / 2;
    glBegin(GL_LINE_LOOP);
        glVertex2f(x - w, y - h); 
        glVertex2f(x - w, y + h);
        glVertex2f(x + w, y + h);
        glVertex2f(x + w, y - h);
    glEnd();
}