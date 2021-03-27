#ifndef __AIRPLANE__
#define __AIRPLANE__

#include <cstdlib>
#include <iostream>
#include <list>
#include <stack>
#include "base/Rect.hpp"
#include "base/Triangle.hpp"
#include "base/ObjectTree.hpp"
#include "3rdobjects/ThirdObjectManager.hpp"

class GamePlay;

class Airplane {
private:
    friend class GamePlay;

public:
    Airplane ();
    ~Airplane ();
    void update (const int bulletDirection);
    void init (const Point2D p, const uint8_t _lives);
    void setSpeed (const GLfloat _speed);
    void setBulletSpeed (const GLfloat _bulletSpeed);
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
    FigureNode* model;
    ThirdObjectManager bulletManager;
    GLfloat speed;
    GLfloat bulletSpeed;
    uint8_t lives;
    int lastActivatedTime;
    int lastDeactivatedTime;
};

#endif