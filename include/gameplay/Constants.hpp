#ifndef __CONSTANTS__
#define __CONSTANTS__

#include <GL/glew.h>
#include <GL/freeglut.h>

const int FPS = 60;
const int TIME_PER_FRAME = 1000 / FPS;

namespace Window {
    const GLint WINDOW_WIDTH = 1024;
    const GLint WINDOW_HEIGHT = 1024;
    const GLfloat MIN_DEPTH = 1000.0f;
    const GLfloat MAX_DEPTH = -1000.0f;
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

const uint8_t INIT_PLAYER_LIVES = 10;
const uint8_t MAX_STAGE = 100;
const GLfloat AIRPLANE_WIDTH = 0.2f;
const GLfloat BULLET_RADIUS = 0.02f;
const GLfloat ITEM_HEIGHT = 0.08f;
const GLfloat ITEM_DURATION_SECS = 5.0f;

namespace WORLD_BOUND {
    const GLfloat LEFT  = -1.0f;
    const GLfloat RIGHT = 1.0f;
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