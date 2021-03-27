#ifndef __OBJECT__
#define __OBJECT__

#include "gameplay/Constants.hpp"
#include "base/core/FigureNode.hpp"

class Object {
public:
    Object ();
    ~Object ();
    void setSpeed (GLfloat _speed);

public:
    void move (const int direction);
    void rotate (const GLfloat degree);

public: 
    virtual void display () const = 0;

private:
    FigureNode* root;
    GLfloat speed;
};

#endif