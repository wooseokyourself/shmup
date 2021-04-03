#ifndef __HEART__
#define __HEART__

#include "base/Object.hpp"

class Heart : public Object {
public:
    Heart ();
    void init (const TransformMatrix& mat, const GLfloat unit, const Rgba color);

public:
    virtual void handlingWhenOutOfBound () { }
    virtual void update ();
    virtual void display () const;

private:
    Object* bottom; // Rect
    Object* left; // Circle
    Object* right; // Circle
};

#endif