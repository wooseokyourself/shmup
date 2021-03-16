#ifndef __CONSTANTS__
#define __CONSTANTS__

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>

const int FPS = 60;
const int TIME_PER_FRAME = 1000 / FPS;

namespace Window {
    const GLint WINDOW_WIDTH = 800;
    const GLint WINDOW_HEIGHT = 800;
};

enum Direction {
    NONE        = 0,
    LEFT        = 0x0064,
    UP          = 0x0065,
    RIGHT       = 0x0066,
    DOWN        = 0x0067,
    LEFT_UP     = 1,
    UP_RIGHT    = 2,
    RIGHT_DOWN  = 3,
    DOWN_LEFT   = 4
};

namespace WORLD_BOUND {
    const GLfloat LEFT  = -0.75f;
    const GLfloat RIGHT = 0.75f;
    const GLfloat UP    = 1.0f;
    const GLfloat DOWN  = -1.0f;
}

namespace AirplaneSpeed {
    const GLfloat FAST = 0.05;
    const GLfloat NORMAL = 0.03;
    const GLfloat SLOW = 0.01;
}

namespace BulletSpeed {
    const GLfloat FAST = 0.05;
    const GLfloat NORMAL = 0.03;
    const GLfloat SLOW = 0.01;
};

#endif