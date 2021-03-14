#include "base/Rectangle.hpp"

/**
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 */
Rectangle::Rectangle (const GLfloat _width, const GLfloat _height)
: x(0), y(0), width(_width), height(_height), color(1.0f, 1.0f, 1.0f) { }

/**
 * @param p The center point axis of the rectangle. (each are -1.0 to 1.0)
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 */
Rectangle::Rectangle (const Point2D p, const GLfloat _width, const GLfloat _height)
: x(p.x), y(p.y), width(_width), height(_height), color(1.0f, 1.0f, 1.0f) { }

/**
 * @param _x The x value of the center point of the rectangle. (-1.0 to 1.0)
 * @param _y The y value of the center point of the rectangle. (-1.0 to 1.0)
 * @param _width (-1.0 to 1.0)
 * @param _height (-1.0 to 1.0)
 */
Rectangle::Rectangle (const GLfloat _x, const GLfloat _y, const GLfloat _width, const GLfloat _height)
: x(_x), y(_y), width(_width), height(_height), color(1.0f, 1.0f, 1.0f) { }

/**
 * @return The point of the left-top of the rectangle.
 */
Point2D Rectangle::getLeftTop () const {
    GLfloat halfWidth = width / 2;
    GLfloat halfHeight = height / 2;
    return Point2D(x - halfWidth, y + halfHeight);
}

/**
 * @return The point of the right-bottom of the rectangle.
 */
Point2D Rectangle::getRightBottom () const {
    GLfloat halfWidth = width / 2;
    GLfloat halfHeight = height / 2;
    return Point2D(x + halfWidth, y - halfHeight);
}

/**
 * @brief Set the x and y of the rectangle.
 * @param _x New x value of the center point of the rectangle.
 * @param _y New y value of the center point of the rectangle.
 */
void Rectangle::setPosition (const GLfloat _x, const GLfloat _y) {
    x = _x;
    y = _y;
}

/**
 * @brief Draw the rectangle in OpenGL world.
 */
void Rectangle::display () const {
    glColor3f(color.R, color.G, color.B);
    GLfloat w = width / 2;
    GLfloat h = height / 2;
    glBegin(GL_LINE_LOOP);
        glVertex2f(x - w, y - h); 
        glVertex2f(x - w, y + h);
        glVertex2f(x + w, y + h);
        glVertex2f(x + w, y - h);
    glEnd();
}

/**
 * @brief Set color of the rectangle.
 * @param R The R value of the rectangle's color. (0.0 to 1.0)
 * @param G The G value of the rectangle's color. (0.0 to 1.0)
 * @param B The B value of the rectangle's color. (0.0 to 1.0)
 */
void Rectangle::setColor (const GLfloat _R, const GLfloat _G, const GLfloat _B) {
    color.R = _R;
    color.G = _G;
    color.B = _B;
}

/**
 * @brief Set color of the rectangle.
 * @param color The 3-tuple of RGB value of the rectangle's color. (each value is 0.0 to 1.0)
 */
void Rectangle::setColor (const Rgb _color) {
    color = _color;
}

/**
 * @brief Set random color of the rectangle.
 */
void Rectangle::setRandomColor () {
    color = Rgb(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
                static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
                static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}