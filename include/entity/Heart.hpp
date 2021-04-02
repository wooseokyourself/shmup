#ifndef __HEART__
#define __HEART__

#include "base/Object.hpp"

class Heart : public Object {
public:
    Heart ();
    ~Heart ();
    void init (const ModelViewMat2D& mat, const GLfloat unit, const Rgba color);

public:
    void handlingWhenOutOfBound ();
    void display () const;

private:
    Rect* bottom;
    Circle* left;
    Circle* right;
};

#endif