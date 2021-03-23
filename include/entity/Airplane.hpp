#ifndef __AIRPLANE__
#define __AIRPLANE__

#include <cstdlib>
#include <iostream>
#include <list>
#include <stack>
#include "base/Rect.hpp"
#include "3rdobjects/ThirdObjectManager.hpp"

class GamePlay;

class Airplane : public Rect {
private:
    friend class GamePlay;

public:
    Airplane (const Point2D p, 
              const GLfloat width, 
              const GLfloat height, 
              const GLfloat speed, 
              const GLfloat _bulletSpeed);
    Airplane (const GLfloat x, 
              const GLfloat y, 
              const GLfloat width, 
              const GLfloat height, 
              const GLfloat speed, 
              const GLfloat _bulletSpeed);
    void update (const int bulletDirection);
    void init (const uint8_t _lives);
    void destruct ();
    void loseLife ();
    bool isAlive () const;
    int getLives () const;
    void fire ();
    int getLastActivatedTime () const;
    int getLastDeactivatedTime () const;

public:
    void display ();

private:
    ThirdObjectManager bulletManager;
    GLfloat bulletSpeed;
    uint8_t lives;
    int lastActivatedTime;
    int lastDeactivatedTime;
};

#endif