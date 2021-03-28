#include "base/core/BaseRect.hpp"

BaseRect::BaseRect ()
: Figure(), width(0.0f), height(0.0f) { }

void BaseRect::setSide (const GLfloat _width, const GLfloat _height) {
    width = _width;
    height = _height;
}

/**
 * @return The point of the left-top of the rectangle in world space.
 */
Point2D BaseRect::getLeftTop () const {
    GLfloat halfWidth = width / 2;
    return Point2D(mat.tx - halfWidth, mat.ty + height);
}

/**
 * @return The point of the right-bottom of the rectangle in world space.
 */
Point2D BaseRect::getRightBottom () const {
    GLfloat halfWidth = width / 2;
    return Point2D(mat.tx + halfWidth, mat.ty - height);
}

void BaseRect::draw () const {
    glTranslatef(mat.tx, mat.ty, 0.0f);
    glRotatef(mat.degree, 0.0f, 0.0f, 1.0f);

    glColor4f(color.R, color.G, color.B, color.A);
    GLfloat halfWidth = width / 2;
    glBegin(GL_POLYGON);
        glVertex2f(-halfWidth, height); 
        glVertex2f(-halfWidth, 0.0f);
        glVertex2f(halfWidth, 0.0f);
        glVertex2f(halfWidth, height);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(-halfWidth, height); 
        glVertex2f(-halfWidth, 0.0f);
        glVertex2f(halfWidth, 0.0f);
        glVertex2f(halfWidth, height);
    glEnd();
}