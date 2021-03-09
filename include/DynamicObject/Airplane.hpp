#ifndef __AIRPLANE__
#define __AIRPLANE__

#include <iostream>
#include "DynamicObject/DynamicObject.hpp"
#include "DynamicObject/BulletManager.hpp"

class EventHandler;

class Airplane : public DynamicObject {
private:
    friend class EventHandler;

public:
    Airplane (const Point p, const GLfloat _width, const GLfloat _height, const GLfloat _speed);
    Airplane (const GLfloat _x, const GLfloat _y, const GLfloat _width, const GLfloat _height, const GLfloat _speed);
    void init (const uint8_t _lives);
    bool isActivated ();
    void destruct ();
    void loseLife ();
    void moveLeft ();
    void moveRight ();
    void moveUp ();
    void moveDown ();
    void fire ();
    void display ();
    void update ();

private:
    BulletManager bulletManager;
    uint8_t lives;
    bool activated;
};

#endif