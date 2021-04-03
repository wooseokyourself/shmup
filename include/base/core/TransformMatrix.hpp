#ifndef __TRANSFORMMATRIX__
#define __TRANSFORMMATRIX__

#include <cmath>
#include <GL/glew.h>

class TransformMatrix {
public:
    TransformMatrix () : tx(0.0f), ty(0.0f), tz(0.0f), sx(1.0f), sy(1.0f), degree(0.0f) { }
    inline void setTranslate (const GLfloat& _tx, const GLfloat& _ty) {
        tx = _tx;
        ty = _ty;
    }
    inline void setTranslate (const GLfloat& _tx, const GLfloat& _ty, const GLfloat& _tz) {
        tx = _tx;
        ty = _ty;
        tz = _tz;
    }
    inline void moveTranslate (const GLfloat& tx, const GLfloat& ty) {
        this->tx += tx;
        this->ty += ty;
    }
    inline void moveTranslate (const GLfloat& tx, const GLfloat& ty, const GLfloat& tz) {
        this->tx += tx;
        this->ty += ty;
        this->tz += tz;
    }
    inline void setRotate (const GLfloat& _degree) {
        degree = _degree;
    }
    inline void rotate (const GLfloat& degree) {
        this->degree = fmodf(this->degree + degree, 360.0f);
    }
    inline void setScale (const GLfloat& _sx, const GLfloat& _sy) {
        sx = _sx;
        sy = _sy;
    }
    inline void scale (const GLfloat& sx, const GLfloat& sy) {
        this->sx += sx;
        this->sy += sy;
    }
    inline void init () {
        tx = 0.0f;
        ty = 0.0f;
        sx = 1.0f;
        sy = 1.0f;
        degree = 0.0f;
    }

public:
    GLfloat tx;
    GLfloat ty;
    GLfloat tz;
    GLfloat sx;
    GLfloat sy;
    GLfloat degree;
};

#endif