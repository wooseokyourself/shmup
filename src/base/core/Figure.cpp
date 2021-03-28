#include "base/core/Figure.hpp"

Figure::Figure ()
: color(1.0f, 1.0f, 1.0f) {
    mat.setTranslate(0.0f, 0.0f, 0.0f);
    mat.setRotate(0.0f);
    mat.setScale(1.0f, 1.0f);
}

Point2D Figure::getWorldPosition () const {
    return Point2D(mat.tx, mat.ty);
}

/**
 * @brief Set color of the object.
 * @param R The R value of the object's color. (0.0 to 1.0)
 * @param G The G value of the object's color. (0.0 to 1.0)
 * @param B The B value of the object's color. (0.0 to 1.0)
 */
void Figure::setColor (const GLfloat _R, const GLfloat _G, const GLfloat _B) {
    color.R = _R;
    color.G = _G;
    color.B = _B;
}

/**
 * @brief Set color of the object.
 * @param color The 3-tuple of RGBA value of the object's color. (each value is 0.0 to 1.0)
 */
void Figure::setColor (const Rgba _color) {
    color = _color;    
}

Rgba Figure::getColor () const {
    return color;
}

/**
 * @brief Set random color of the object.
 */
void Figure::setRandomColor () {
    color = Rgba(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
                static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
                static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

ModelViewMat2D Figure::getMatrix () const {
    return mat;
}

void Figure::setMatrix (const ModelViewMat2D& mat) {
    setTranslate(mat.tx, mat.ty);
    setRotate(mat.degree);
    setScale(mat.sx, mat.sy);
} 

void Figure::clearMatrix () {
    setTranslate(0.0f, 0.0f);
    setRotate(0.0f);
    setScale(1.0f, 1.0f);
}

/**
 * @brief Set the x and y of the object.
 * @param p New point of the center point of the object in world space.
 */
void Figure::setTranslate (const Point2D p) {
    mat.setTranslate(p.x, p.y);
}

/**
 * @brief Set the x and y of the object.
 * @param x New x value of the center point of the object in world space.
 * @param y New y value of the center point of the object in world space.
 */
void Figure::setTranslate (const GLfloat x, const GLfloat y) {
    mat.setTranslate(x, y);
}

void Figure::setTranslate (const GLfloat x, const GLfloat y, const GLfloat z) {
    mat.setTranslate(x, y, z);
}

void Figure::translate (const Point2D p) {
    mat.moveTranslate(p.x, p.y);
}

void Figure::translate (const GLfloat x, const GLfloat y) {
    mat.moveTranslate(x, y);
}

void Figure::translate (const GLfloat x, const GLfloat y, const GLfloat z) {
    mat.moveTranslate(x, y, z);
}


void Figure::setRotate (const GLfloat degree) {
    mat.setRotate(degree);
}

void Figure::rotate (const GLfloat degree) {
    mat.rotate(degree);
}

void Figure::setScale (const GLfloat x, const GLfloat y) {
    mat.setScale(x, y);
}

void Figure::scale (const GLfloat x, const GLfloat y) {
    mat.scale(x, y);
}