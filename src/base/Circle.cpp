#include "base/Circle.hpp"

Circle::Circle (const GLfloat _radius)
: Object(), radius(_radius) { }

Circle::Circle (const Point2D p, const GLfloat _radius)
: Object(p), radius(_radius) { }

Circle::Circle (const GLfloat x, const GLfloat y, const GLfloat _radius)
: Object(x, y), radius(_radius) { }

void Circle::display () const {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(mat.tx, mat.ty, 0.0f);
    glColor4f(color.R, color.G, color.B, color.A);

    // draw refer: https://stackoverflow.com/questions/22444450/drawing-circle-with-opengl
    int segment = 30;
    glBegin(GL_POLYGON);
    for (int i = 0 ; i < segment ; i ++)   {
        float theta = 2.0f * 3.1415926f * float(i) / float(segment);//get the current angle 
        float x = radius * cosf(theta);//calculate the x component 
        float y = radius * sinf(theta);//calculate the y component 
        // glVertex2f(x + mat.sx, y + mat.sy);//output vertex 
        glVertex2f(x, y);
    }
    glEnd();
    glBegin(GL_LINE_LOOP);
    for (int i = 0 ; i < segment ; i ++)   {
        float theta = 2.0f * 3.1415926f * float(i) / float(segment);//get the current angle 
        float x = radius * cosf(theta);//calculate the x component 
        float y = radius * sinf(theta);//calculate the y component 
        // glVertex2f(x + mat.sx, y + mat.sy);//output vertex 
        glVertex2f(x, y);
    }
    glEnd();
}