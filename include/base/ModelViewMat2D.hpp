#ifndef __MODELVIEWMAT2D__
#define __MODELVIEWMAT2D__

#include <glm/glm.hpp>
#include <GL/glew.h>

class ModelViewMat2D {
public:
    ModelViewMat2D ();
    void setTranslate (const GLfloat& _tx, const GLfloat& _ty);
    void moveTranslate (const GLfloat& _tx, const GLfloat& _ty);
    void setRotate (const GLfloat& _theta);
    void setScale (const GLfloat& _sx, const GLfloat& _sy);
    void init ();

public:
    GLfloat tx;
    GLfloat ty;
    GLfloat sx;
    GLfloat sy;
    GLfloat theta;
};

#endif