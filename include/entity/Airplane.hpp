#ifndef __AIRPLANE__
#define __AIRPLANE__

#include <cstdlib>
#include <iostream>
#include <list>
#include <stack>
#include "base/Object.hpp"
#include "entity/ThirdObjectManager.hpp"

class GamePlay;

class Airplane : public Object {
private:
    friend class GamePlay;

public:
    Airplane ();
    ~Airplane ();
    void update (const int bulletDirection);
    void init (const ModelViewMat2D& mat, const uint8_t _lives, const GLfloat width, const GLfloat _speed, const GLfloat _bulletSpeed);
    void setSpeed (const GLfloat _speed);
    void setBulletSpeed (const GLfloat _bulletSpeed);
    void destruct ();
    void loseLife ();
    bool isAlive () const;
    int getLives () const;
    void fire ();
    Point2D getHitboxLeftTop () const;
    Point2D getHitboxRightBottom () const;
    ModelViewMat2D getModelViewMatrix () const;
    int getLastActivatedTime () const;
    int getLastDeactivatedTime () const;

public:
    void display () const;

private:
    ThirdObjectManager bulletManager;
    Rect* base; // hitbox
    Rect* body;
    Triangle* head;

    GLfloat bulletSpeed;
    uint8_t lives;
    int lastActivatedTime;
    int lastDeactivatedTime;
};

#endif