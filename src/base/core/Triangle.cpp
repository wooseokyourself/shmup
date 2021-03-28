#include "base/core/Triangle.hpp"

Triangle::Triangle ()
: Figure(), radius(0.0f) { }

void Triangle::setRadius (const GLfloat _radius) {
    radius = _radius;
}

void Triangle::draw () const {
    glTranslatef(mat.tx, mat.ty, mat.tz);
    glRotatef(mat.degree, 0.0f, 0.0f, 1.0f);

    glColor4f(color.R, color.G, color.B, color.A);
    // draw refer: https://stackoverflow.com/questions/22444450/drawing-circle-with-opengl
    int segment = 3;
    glBegin(GL_POLYGON);
    for (int i = 0 ; i < segment ; i ++)   {
        float degree = 2.0f * 3.1415926f * float(i) / float(segment);//get the current angle 
        float x = radius * cosf(degree);//calculate the x component 
        float y = radius * sinf(degree);//calculate the y component 
        glVertex2f(x, y);
    }
    glEnd();
    glBegin(GL_LINE_LOOP);
    for (int i = 0 ; i < segment ; i ++)   {
        float degree = 2.0f * 3.1415926f * float(i) / float(segment);//get the current angle 
        float x = radius * cosf(degree);//calculate the x component 
        float y = radius * sinf(degree);//calculate the y component 
        glVertex2f(x, y);
    }
    glEnd();
}