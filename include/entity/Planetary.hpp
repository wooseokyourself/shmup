#ifndef __PLANETARY__
#define __PLANETARY__

#include "base/Object.hpp"

class Planetary : public Object {
public:
    Planetary ();
    void init (const TransformMatrix& mat, const GLfloat starRadius);

public:
    virtual void update ();

private:
    Object* star; // Circle
    Object* orbit; // Circle
    Object* satellite; // Circle
    GLfloat starAngle;
    GLfloat orbitAngle;
};

#endif