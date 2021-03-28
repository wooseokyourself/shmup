#include "base/core/ModelViewMat2D.hpp"

ModelViewMat2D::ModelViewMat2D ()
: tx(0.0f), ty(0.0f), tz(0.0f), sx(1.0f), sy(1.0f), degree(0.0f) { }

void ModelViewMat2D::setTranslate (const GLfloat& _tx, const GLfloat& _ty) {
    tx = _tx;
    ty = _ty;
}

void ModelViewMat2D::setTranslate (const GLfloat& _tx, const GLfloat& _ty, const GLfloat& _tz) {
    tx = _tx;
    ty = _ty;
    tz = _tz;
}

void ModelViewMat2D::moveTranslate (const GLfloat& tx, const GLfloat& ty) {
    this->tx += tx;
    this->ty += ty;
}

void ModelViewMat2D::moveTranslate (const GLfloat& tx, const GLfloat& ty, const GLfloat& tz) {
    this->tx += tx;
    this->ty += ty;
    this->tz += tz;
}

void ModelViewMat2D::setRotate (const GLfloat& _degree) {
    degree = _degree;
}

void ModelViewMat2D::rotate (const GLfloat& degree) {
    this->degree = fmodf(this->degree + degree, 360.0f);
}

void ModelViewMat2D::setScale (const GLfloat& _sx, const GLfloat& _sy) {
    sx = _sx;
    sy = _sy;
}

void ModelViewMat2D::init () {
    tx = 0.0f;
    ty = 0.0f;
    sx = 0.0f;
    sy = 0.0f;
    degree = 0.0f;
}

void ModelViewMat2D::scale (const GLfloat& sx, const GLfloat& sy) {
    this->sx += sx;
    this->sy += sy;
}