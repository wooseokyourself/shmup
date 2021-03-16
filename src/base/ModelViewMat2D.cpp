#include "base/ModelViewMat2D.hpp"

ModelViewMat2D::ModelViewMat2D ()
: tx(0.0f), ty(0.0f), sx(1.0f), sy(1.0f), theta(0.0f) { }

void ModelViewMat2D::setTranslate (const GLfloat& _tx, const GLfloat& _ty) {
    tx = _tx;
    ty = _ty;
}

void ModelViewMat2D::moveTranslate (const GLfloat& _tx, const GLfloat& _ty) {
    tx += _tx;
    ty += _ty;
}

void ModelViewMat2D::setRotate (const GLfloat& _theta) {
    theta = _theta;
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
    theta = 0.0f;
}