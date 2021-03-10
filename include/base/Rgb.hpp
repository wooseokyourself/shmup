#ifndef __RGB__
#define __RGB__

#include <GL/glew.h>

struct Rgb {
    Rgb(GLfloat _R, GLfloat _G, GLfloat _B) : R(_R), G(_G), B(_B) { }
    GLfloat R;
    GLfloat G;
    GLfloat B;
};

#endif