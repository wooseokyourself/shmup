#include "base/Rect.hpp"

/**
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 */
Rect::Rect (const GLfloat _width, const GLfloat _height)
: width(_width), height(_height), color(1.0f, 1.0f, 1.0f) {
    // mat.setScale(1.0f, GLfloat(Window::WINDOW_WIDTH / Window::WINDOW_HEIGHT));
    mat.setScale(1.0f, 1.0f);
}

/**
 * @param p The center point axis of the rectangle in world space. (each are -1.0 to 1.0)
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 */
Rect::Rect (const Point2D p, const GLfloat _width, const GLfloat _height)
: width(_width), height(_height), color(1.0f, 1.0f, 1.0f) {
    mat.setTranslate(p.x, p.y);
    // mat.setScale(1.0f, GLfloat(Window::WINDOW_WIDTH / Window::WINDOW_HEIGHT));
    mat.setScale(1.0f, 1.0f);
}

/**
 * @param x The x value of the center point of the rectangle in world space. (-1.0 to 1.0)
 * @param y The y value of the center point of the rectangle in world space. (-1.0 to 1.0)
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 */
Rect::Rect (const GLfloat x, const GLfloat y, const GLfloat _width, const GLfloat _height)
: width(_width), height(_height), color(1.0f, 1.0f, 1.0f) {
    mat.setTranslate(x, y);
    // mat.setScale(1.0f, GLfloat(Window::WINDOW_WIDTH / Window::WINDOW_HEIGHT));
    mat.setScale(1.0f, 1.0f);
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

/**
 * @brief Set the x and y of the rectangle.
 * @param x New x value of the center point of the rectangle in world space.
 * @param y New y value of the center point of the rectangle in world space.
 */
void Rect::setPosition (const GLfloat x, const GLfloat y) {
    mat.setTranslate(x, y);
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

/**
 * @brief Set color of the rectangle.
 * @param R The R value of the rectangle's color. (0.0 to 1.0)
 * @param G The G value of the rectangle's color. (0.0 to 1.0)
 * @param B The B value of the rectangle's color. (0.0 to 1.0)
 */
void Rect::setColor (const GLfloat _R, const GLfloat _G, const GLfloat _B) {
    color.R = _R;
    color.G = _G;
    color.B = _B;
}

/**
 * @brief Set color of the rectangle.
 * @param color The 3-tuple of RGB value of the rectangle's color. (each value is 0.0 to 1.0)
 */
void Rect::setColor (const Rgb _color) {
    color = _color;
}

/**
 * @brief Set random color of the rectangle.
 */
void Rect::setRandomColor () {
    color = Rgb(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
                static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
                static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}