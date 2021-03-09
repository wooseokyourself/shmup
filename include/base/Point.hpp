#ifndef __DATASTRUCTURES__
#define __DATASTRUCTURES__

#include <GL/glew.h>

struct Point {
    Point(GLfloat _x, GLfloat _y) : x(_x), y(_y) { }
    GLfloat x;
    GLfloat y;
};

#endif