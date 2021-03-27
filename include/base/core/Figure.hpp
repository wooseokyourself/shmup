#ifndef __FIGURE__
#define __FIGURE__

#include "base/core/Point2D.hpp"
#include "base/core/Rgba.hpp"
#include "base/core/ModelViewMat2D.hpp"
#include "gameplay/Constants.hpp"
#include <cstdlib>
#include <GL/glut.h>

class Figure {
public:
    Figure ();
    Point2D getWorldPosition () const;
    void setColor (const GLfloat _R, const GLfloat _G, const GLfloat _B);
    void setColor (const Rgba _color);
    void setRandomColor ();

public:
    ModelViewMat2D getMatrix () const;
    void setMatrix (const ModelViewMat2D& mat);
    void clearMatrix ();
    void setTranslate (const Point2D p);
    void setTranslate (const GLfloat x, const GLfloat y);
    void translate (const Point2D p);
    void translate (const GLfloat x, const GLfloat y);
    void setRotate (const GLfloat degree);
    void rotate (const GLfloat degree);
    void setScale (const GLfloat x, const GLfloat y);
    void scale (const GLfloat x, const GLfloat y);

public:
    virtual void draw () const = 0;

protected:
    Rgba color;
    ModelViewMat2D mat;
};

#endif