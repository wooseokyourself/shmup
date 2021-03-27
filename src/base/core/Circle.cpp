#include "base/core/Circle.hpp"

Circle::Circle ()
: Figure(), radius(0.0f) { }

void Circle::setRadius (const GLfloat _radius) {
    radius = _radius;
}

/*
void Circle::display () {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    draw();
}
*/

void Circle::draw () const {
    glTranslatef(mat.tx, mat.ty, 0.0f);
    glRotatef(mat.degree, 0.0f, 0.0f, 1.0f);

    glColor4f(color.R, color.G, color.B, color.A);
    // draw refer: https://stackoverflow.com/questions/22444450/drawing-circle-with-opengl
    int segment = 30;
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