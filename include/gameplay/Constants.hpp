#ifndef __CONSTANTS__
#define __CONSTANTS__

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