#include "base/Rect.hpp"

/**
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 */
Rect::Rect (const GLfloat _width, const GLfloat _height)
: Object(), width(_width), height(_height) { }

/**
 * @param p The center point axis of the rectangle in world space. (each are -1.0 to 1.0)
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 */
Rect::Rect (const Point2D p, const GLfloat _width, const GLfloat _height)
: Object(p), width(_width), height(_height) { }

/**
 * @param x The x value of the center point of the rectangle in world space. (-1.0 to 1.0)
 * @param y The y value of the center point of the rectangle in world space. (-1.0 to 1.0)
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 */
Rect::Rect (const GLfloat x, const GLfloat y, const GLfloat _width, const GLfloat _height)
: Object(x, y), width(_width), height(_height) { }

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

/**
 * @brief Draw the rectangle in OpenGL world.
 */
void Rect::display () const {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(mat.tx, mat.ty, 0.0f);
    // glScalef(mat.sx, mat.sy, 1.0f);
    glColor3f(color.R, color.G, color.B);
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
}