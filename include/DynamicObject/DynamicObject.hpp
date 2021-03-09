#ifndef __DYNAMICOBJECT__
#define __DYNAMICOBJECT__

#include "DataStructures.hpp"
#include <GL/glut.h>
#include <GL/gl.h>

class DynamicObject {
public:
    DynamicObject (const GLfloat _width, const GLfloat _height, const GLfloat _speed);
    DynamicObject (const Point p, const GLfloat _width, const GLfloat _height, const GLfloat _speed);
    DynamicObject (const GLfloat _x, const GLfloat _y, const GLfloat _width, const GLfloat _height, const GLfloat _speed);
    Point getLeftTop ();
    Point getRightBottom ();
    void setPosition (const GLfloat _x, const GLfloat _y);
    void moveLeft ();
    void moveRight ();
    void moveUp ();
    void moveDown ();
    void display (const GLfloat R, const GLfloat G, const GLfloat B);
    bool isOutOfBound ();

protected:
    GLfloat x; // center
    GLfloat y; // center
    GLfloat width;
    GLfloat height;
    GLfloat speed;
};

#endif