#ifndef __AIRPLANE__
#define __AIRPLANE__

#include <iostream>
#include <list>
#include <stack>
#include "base/DynamicObject.hpp"
#include "dynamics/Bullet.hpp"

#define MAX_BULLETS 100

class GamePlay;

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

class Airplane : public DynamicObject {
private:
    class BulletManager {
    public:
        BulletManager (const GLfloat bulletWidth, const GLfloat bulletHeight, const GLfloat bulletSpeed);
        ~BulletManager ();
        void activateBullet (const GLfloat x, const GLfloat y);
        void display (const GLfloat R, const GLfloat G, const GLfloat B) const;
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
    Airplane (const Point p, 
              const GLfloat _width, 
              const GLfloat _height, 
              const GLfloat _speed, 
              const GLfloat bulletSpeed);
    Airplane (const GLfloat _x, 
              const GLfloat _y, 
              const GLfloat _width, 
              const GLfloat _height, 
              const GLfloat _speed, 
              const GLfloat bulletSpeed);
    void update (const int bulletDirection);
    void init (const uint8_t _lives);
    void destruct ();
    void loseLife ();
    bool isAlive () const;
    void fire ();
    void setColor (const GLfloat _R, const GLfloat _G, const GLfloat _B);
    void setColor (const Rgb _color);
    void display () const ;
    int getLastActivatedTime () const;
    int getLastDeactivatedTime () const;

private:
    BulletManager bulletManager;
    uint8_t lives;
    int lastActivatedTime;
    int lastDeactivatedTime;
    Rgb color;
};

#endif