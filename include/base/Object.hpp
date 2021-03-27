#ifndef __OBJECT__
#define __OBJECT__

#include "base/core/Circle.hpp"
#include "base/core/Rect.hpp"
#include "base/core/BaseRect.hpp"
#include "base/core/Triangle.hpp"
#include "base/core/FigureNode.hpp"
#include "gameplay/Constants.hpp"

class Object {
public:
    Object ();
    ~Object ();
    virtual void display () const = 0;
    void setSpeed (GLfloat _speed);
    bool isOutOfBound (const int bound);
    bool isIn (const Point2D leftTop, const Point2D rightBottom);

public:
    void move (const int direction);
    void rotate (const GLfloat degree);

protected:
    FigureNode* root;
    GLfloat speed;
};

#endif