#include "base/Rectangle.hpp"

Rectangle::Rectangle (const GLfloat _width, const GLfloat _height)
: x(0), y(0), width(_width), height(_height), color(1.0f, 1.0f, 1.0f) { }

Rectangle::Rectangle (const Point p, const GLfloat _width, const GLfloat _height)
: x(p.x), y(p.y), width(_width), height(_height), color(1.0f, 1.0f, 1.0f) { }

Rectangle::Rectangle (const GLfloat _x, const GLfloat _y, const GLfloat _width, const GLfloat _height)
: x(_x), y(_y), width(_width), height(_height), color(1.0f, 1.0f, 1.0f) { }

Point Rectangle::getLeftTop () const {
    GLfloat halfWidth = width / 2;
    GLfloat halfHeight = height / 2;
    return Point(x - halfWidth, y + halfHeight);
}

Point Rectangle::getRightBottom () const {
    GLfloat halfWidth = width / 2;
    GLfloat halfHeight = height / 2;
    return Point(x + halfWidth, y - halfHeight);
}

void Rectangle::setPosition (const GLfloat _x, const GLfloat _y) {
    x = _x;
    y = _y;
}

void Rectangle::display (const GLfloat R, const GLfloat G, const GLfloat B) const {
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

void Rectangle::display (const Rgb color) const {
    display(color.R, color.G, color.B);
}

void Rectangle::setColor (const GLfloat _R, const GLfloat _G, const GLfloat _B) {
    color.R = _R;
    color.G = _G;
    color.B = _B;
}

void Rectangle::setColor (const Rgb _color) {
    color = _color;
}

void Rectangle::setRandomColor () {
    color = Rgb(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
                static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
                static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}