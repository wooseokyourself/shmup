#include "base/Triangle.hpp"

Triangle::Triangle (const GLfloat _radius)
: Object(), radius(_radius) { }

Triangle::Triangle (const Point2D p, const GLfloat _radius)
: Object(p), radius(_radius) { }

Triangle::Triangle (const GLfloat x, const GLfloat y, const GLfloat _radius)
: Object(x, y), radius(_radius) { }

void Triangle::display () const {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(mat.tx, mat.ty, 0.0f);
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