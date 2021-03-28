#ifndef __BULLET__
#define __BULLET__

#include "base/Object.hpp"
#include <cmath>

class Bullet : public Object {
public:
    Bullet ();
    ~Bullet ();
    void init (const ModelViewMat2D& mat, const GLfloat radius, const Rgba color, const GLfloat speed);
    void move ();
    void display () const;
};
#endif