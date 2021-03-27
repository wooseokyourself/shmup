#ifndef __ITEM__
#define __ITEM__

#include "base/ThirdObject.hpp"
#include "base/Triangle.hpp"

#define MAX_ITEMS 10

class Item : public ThirdObject {
public:
    void init (const GLfloat length, const ModelViewMat2D& mat, const Rgba color, const GLfloat speed);
    void display ();
    void draw () const;

private:
    GLfloat radius;
    Triangle top;
    Triangle bottom;
};

#endif