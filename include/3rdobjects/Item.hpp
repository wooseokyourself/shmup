#ifndef __ITEM__
#define __ITEM__

#include "3rdobjects/ThirdObject.hpp"
#include "base/Triangle.hpp"

#define MAX_ITEMS 10

class Item : public ThirdObject {
public:
    void init (const GLfloat length, const ModelViewMat2D& mat, const Rgba color, const GLfloat speed);
    void display ();

private:
    GLfloat radius;
    Triangle top;
    Triangle bottom;
};

#endif