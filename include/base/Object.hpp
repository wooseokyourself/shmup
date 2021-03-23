#ifndef __OBJECT__
#define __OBJECT__

#include "base/Point2D.hpp"
#include "base/Rgba.hpp"
#include "base/ModelViewMat2D.hpp"
#include "gameplay/Constants.hpp"
#include <cstdlib>
#include <GL/glut.h>

class Object {
public:
    Object ();
    Point2D getWorldPosition () const;
    void setPosition (const Point2D p);
    void setPosition (const GLfloat x, const GLfloat y);
    void setColor (const GLfloat _R, const GLfloat _G, const GLfloat _B);
    void setColor (const Rgba _color);
    void setRandomColor ();
    void setSpeed (const GLfloat _speed);
    void move (const int direction);
    void setRotate (const GLfloat degree);
    void rotate (const GLfloat degree);
    void setScale (const GLfloat x, const GLfloat y);
    void scale (const GLfloat x, const GLfloat y);

public:
    virtual void display () = 0;

protected:
    Rgba color;
    ModelViewMat2D mat;
    GLfloat speed;
    uint8_t direction;
};

#endif