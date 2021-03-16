#ifndef __AIRPLANE__
#define __AIRPLANE__

#include <cstdlib>
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
        BulletManager (const GLfloat bulletWidth,
                       const GLfloat bulletHeight, 
                       const GLfloat bulletSpeed);
        ~BulletManager ();
        void activateBullet (const ModelViewMat2D& mat, const Rgb& color);
        void display () const;
        void update (const int bulletDirection);
        size_t getActivatedBulletsNumber () const;
        bool deactivateBulletWhichIsIn (const Point2D leftTop, const Point2D rightBottom);

    private:
        std::list<Bullet*> activeBullets;
        std::stack<Bullet*> pool;
    };
    
private:
    friend class GamePlay;

public:
    Airplane (const Point2D p, 
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
    int getLives () const;
    void fire ();
    void display () const ;
    int getLastActivatedTime () const;
    int getLastDeactivatedTime () const;

private:
    BulletManager bulletManager;
    uint8_t lives;
    int lastActivatedTime;
    int lastDeactivatedTime;
};

#endif