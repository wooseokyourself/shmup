#ifndef __MODELVIEWMAT2D__
#define __MODELVIEWMAT2D__

#include <cmath>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "gameplay/Constants.hpp"

class ModelViewMat2D {
public:
    ModelViewMat2D ();
    void setTranslate (const GLfloat& _tx, const GLfloat& _ty);
    void setTranslate (const GLfloat& _tx, const GLfloat& _ty, const GLfloat& _tz);
    void moveTranslate (const GLfloat& tx, const GLfloat& ty);
    void moveTranslate (const GLfloat& tx, const GLfloat& ty, const GLfloat& tz);
    void setRotate (const GLfloat& _degree);
    void rotate (const GLfloat& degree);
    void setScale (const GLfloat& _sx, const GLfloat& _sy);
    void scale (const GLfloat& sx, const GLfloat& sy);
    void init ();

public:
    GLfloat tx;
    GLfloat ty;
    GLfloat tz;
    GLfloat sx;
    GLfloat sy;
    GLfloat degree;
};

#endif