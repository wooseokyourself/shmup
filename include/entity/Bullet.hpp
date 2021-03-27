#ifndef __BULLET__
#define __BULLET__

#include "base/Object.hpp"

#include <iostream>

class Bullet : public Object {
public:
    Bullet ();
    ~Bullet ();
    void init (const GLfloat radius, const ModelViewMat2D& mat, const Rgba color, const GLfloat speed);
    void display () const;
};
#endif