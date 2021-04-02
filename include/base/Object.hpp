#ifndef __OBJECT__
#define __OBJECT__

#include "base/core/Utility.hpp"
#include "base/core/Circle.hpp"
#include "base/core/Rect.hpp"
#include "base/core/BaseRect.hpp"
#include "base/core/Triangle.hpp"
#include "base/core/Text.hpp"
#include "base/core/FigureNode.hpp"
#include "gameplay/Constants.hpp"

class Object {
public:
    Object ();
    ~Object ();
    void setSpeed (GLfloat _speed);
    bool isIn (const Point2D leftTop, const Point2D rightBottom) const;

public:
    void move (const GLfloat degree);
    void rotate (const GLfloat degree);
    bool isCenterOutOfBound () const;

public:
    virtual void handlingWhenOutOfBound () = 0;
    virtual void display () const = 0;

protected:
    FigureNode* root;
    GLfloat speed;
};

#endif