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
    void moveTranslate (const GLfloat& _tx, const GLfloat& _ty);
    void setRotate (const GLfloat& _degree);
    void rotate (const GLfloat& accDegree);
    void setScale (const GLfloat& _sx, const GLfloat& _sy);
    void scale (const GLfloat& x, const GLfloat& y);
    void init ();

public:
    GLfloat tx;
    GLfloat ty;
    GLfloat sx;
    GLfloat sy;
    GLfloat degree;
};

#endif