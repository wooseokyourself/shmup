#ifndef __BULLETMANAGER__
#define __BULLETMANAGER__

#define MAX_BULLETS 100

#include <list>
#include <stack>
#include "DynamicObject/Bullet.hpp"

class BulletManager {
public:
    BulletManager (const GLfloat bulletWidth, const GLfloat bulletHeight, const GLfloat bulletSpeed);
    ~BulletManager ();
    void activateBullet (const GLfloat x, const GLfloat y);
    void display ();
    void update ();
    size_t activatedBulletsNumber ();
    bool deactivateBulletIfItsIn (const Point leftTop, const Point rightBottom);

private:
    std::list<Bullet*> activeBullets;
    std::stack<Bullet*> pool;
};

#endif