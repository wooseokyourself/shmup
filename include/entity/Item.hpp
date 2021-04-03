#ifndef __ITEM__
#define __ITEM__

#include "base/core/Utility.hpp"
#include "base/Object.hpp"

#define MAX_ITEMS 10

class Item : public Object {
public:
    Item ();
    void init (const TransformMatrix& mat, const GLfloat length, const Rgba color, const GLfloat speed);
    bool isDurationTimeout () const;

public:
    virtual void handlingWhenOutOfBound ();
    virtual void update ();
    virtual void display () const;

private:
    Object* top; // Triangle
    Object* bottom; // Triangle
    GLfloat activatedTime;
};

#endif