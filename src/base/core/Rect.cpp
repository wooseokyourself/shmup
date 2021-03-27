#include "base/core/Rect.hpp"

Rect::Rect ()
: Figure(), width(0.0f), height(0.0f) { }

void Rect::setSide (const GLfloat _width, const GLfloat _height) {
    width = _width;
    height = _height;
}

/**
 * @return The point of the left-top of the rectangle in world space.
 */
Point2D Rect::getLeftTop () const {
    GLfloat halfWidth = width / 2;
    GLfloat halfHeight = height / 2;
    return Point2D(mat.tx - halfWidth, mat.ty + halfHeight);
}

/**
 * @return The point of the right-bottom of the rectangle in world space.
 */
Point2D Rect::getRightBottom () const {
    GLfloat halfWidth = width / 2;
    GLfloat halfHeight = height / 2;
    return Point2D(mat.tx + halfWidth, mat.ty - halfHeight);
}

/*
void Rect::display () {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    draw();
}
*/

void Rect::draw () const {
    glPushMatrix();
    glPushMatrix();
    glTranslatef(mat.tx, mat.ty, 0.0f);
    glRotatef(mat.degree, 0.0f, 0.0f, 1.0f);

    glColor4f(color.R, color.G, color.B, color.A);
    GLfloat w = width / 2;
    GLfloat h = height / 2;
    glBegin(GL_POLYGON);
        glVertex2f(-w, -h); 
        glVertex2f(-w, h);
        glVertex2f(w, h);
        glVertex2f(w, -h);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(-w, -h); 
        glVertex2f(-w, h);
        glVertex2f(w, h);
        glVertex2f(w, -h);
    glEnd();
    
    glPopMatrix();
    glPopMatrix();
}