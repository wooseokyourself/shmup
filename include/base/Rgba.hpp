#ifndef __RGBA__
#define __RGBA__

#include <GL/glew.h>

struct Rgba {
    Rgba(GLfloat _R, GLfloat _G, GLfloat _B) : R(_R), G(_G), B(_B), A(1.0f) { }
    Rgba(GLfloat _R, GLfloat _G, GLfloat _B, GLfloat _A) : R(_R), G(_G), B(_B), A(_A) { }
    GLfloat R;
    GLfloat G;
    GLfloat B;
    GLfloat A;
};

#endif