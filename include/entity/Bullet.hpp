#ifndef __BULLET__
#define __BULLET__

#include "base/core/Utility.hpp"
#include "base/Object.hpp"
#include <cmath>

class Bullet : public Object {
public:
    Bullet ();
    ~Bullet ();
    void init (const TransformMatrix& mat, const GLfloat radius, const Rgba color, const GLfloat speed);
    bool isOutOfBound () const;

public:
    virtual void handlingWhenOutOfBound ();
    virtual void update ();
    virtual void display () const;

private:
    bool outOfBound;
};
#endif