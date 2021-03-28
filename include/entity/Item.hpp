#ifndef __ITEM__
#define __ITEM__

#include "base/core/Utility.hpp"
#include "base/Object.hpp"

#define MAX_ITEMS 10

class Item : public Object {
public:
    Item ();
    ~Item ();
    void init (const ModelViewMat2D& mat, const GLfloat length, const Rgba color, const GLfloat speed);
    void setRandomRotate ();
    bool shouldBeRemoved ();
    void move ();
    void display () const;

private:
    Rect* base;
    GLfloat activatedTime;
};

#endif