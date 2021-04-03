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
    void init (const TransformMatrix& mat, const uint8_t _lives, const GLfloat width, const GLfloat _speed, const GLfloat _bulletSpeed);
    void setBulletSpeed (const GLfloat _bulletSpeed);
    void destruct ();
    void loseLife ();
    bool isAlive () const;
    int getLives () const;
    void fire (ThirdObjectManager* bulletManager);
    Point2D getHitboxLeftTop () const;
    Point2D getHitboxRightBottom () const;
    int getLastActivatedTime () const;
    int getLastDeactivatedTime () const;
    void setRandomColor ();
    void addShotgunBullet ();

public:
    virtual void handlingWhenOutOfBound ();
    virtual void update ();
    virtual void display () const;

private:
    Rect* hitbox; // same pointer as Object::figure;
    Object* body; // Rect
    Object* head; // Triangle
    Object* leftArm; // BaseRect
    Object* rightArm; // BaseRect
    Object* leftCanon; // BaseRect
    Object* rightCanon; // BaseRect

    uint8_t shotgunBulletNumber;
    GLfloat bulletSpeed;
    uint8_t lives;
    int lastActivatedTime;
    int lastDeactivatedTime;

private:
    uint8_t updateCount;
    bool idleMotionToken;
};

#endif