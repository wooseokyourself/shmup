#ifndef __AIRPLANE__
#define __AIRPLANE__

#include <iostream>
#include <list>
#include <stack>
#include "base/DynamicObject.hpp"
#include "dynamics/Bullet.hpp"

#define MAX_BULLETS 100

class GamePlay;

class Airplane : public DynamicObject {
private:
    class BulletManager {
    public:
        BulletManager (const GLfloat bulletWidth, const GLfloat bulletHeight, const GLfloat bulletSpeed);
        ~BulletManager ();
        void activateBullet (const GLfloat x, const GLfloat y);
        void display ();
        void update (const int bulletDirection);
        size_t activatedBulletsNumber ();
        bool deactivateBulletIfItsIn (const Point leftTop, const Point rightBottom);

    private:
        std::list<Bullet*> activeBullets;
        std::stack<Bullet*> pool;
    };
private:
    friend class GamePlay;

public:
    Airplane (const Point p, const GLfloat _width, const GLfloat _height, const GLfloat _speed);
    Airplane (const GLfloat _x, const GLfloat _y, const GLfloat _width, const GLfloat _height, const GLfloat _speed);
    void update (const int bulletDirection);
    void init (const uint8_t _lives);
    bool isActivated ();
    void destruct ();
    void loseLife ();
    void fire ();
    void display ();

private:
    BulletManager bulletManager;
    uint8_t lives;
    bool activated;
};

#endif