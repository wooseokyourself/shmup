#ifndef __FIGURE__
#define __FIGURE__

#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdlib>

enum Figures {
    CIRCLE,
    RECT,
    BASERECT,
    TRIANGLE,
    TEXT
};

class Figure {
public:
    inline virtual void draw () const = 0;
};

#endif