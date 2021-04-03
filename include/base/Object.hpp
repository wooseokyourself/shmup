#ifndef __OBJECT__
#define __OBJECT__

#include <list>

#include "base/core/Utility.hpp"
#include "base/core/TransformMatrix.hpp"
#include "base/core/Rgba.hpp"
#include "base/core/Point2D.hpp"
#include "base/core/Circle.hpp"
#include "base/core/Rect.hpp"
#include "base/core/BaseRect.hpp"
#include "base/core/Triangle.hpp"
#include "base/core/Text.hpp"
#include "gameplay/Constants.hpp"

enum Priority {
    FRONT, 
    BACK
};

class Object {
public:
    Object ();
    ~Object ();

public: // Graph API
    Figure* setFigure (const int figureType);
    Figure* operator * ();
    Object* pushChild (Object* child);
    Object* pushChild (Object* child, const int priority);
    Object* pushChild (const int figureType);
    Object* pushChild (const int figureType, const int priority);
    void popBackChild ();
    void popFrontChild ();
    std::list<Object*>& getChildren ();

public: // Transformations
    TransformMatrix getModelViewMatrix () const;
    void setMatrix (const TransformMatrix& mat);
    void clearMatrix ();
    void setTranslate (const Point2D p);
    void setTranslate (const GLfloat x, const GLfloat y);
    void setTranslate (const GLfloat x, const GLfloat y, const GLfloat z);
    void translate (const Point2D p);
    void translate (const GLfloat x, const GLfloat y);
    void translate (const GLfloat x, const GLfloat y, const GLfloat z);
    void setRotate (const GLfloat degree);
    void rotate (const GLfloat degree);
    void setScale (const GLfloat x, const GLfloat y);
    void scale (const GLfloat x, const GLfloat y);

public: // Colors
    void setColor (const GLfloat _R, const GLfloat _G, const GLfloat _B);
    void setColor (const GLfloat _R, const GLfloat _G, const GLfloat _B, const GLfloat _A);
    void setColor (const Rgba _color);
    Rgba getColor () const;
    void setRandomColor ();
    void setColorAlpha (const GLfloat _A);

public: // Utilities
    Point2D getWorldPosition () const;
    void setSpeed (GLfloat _speed);
    GLfloat getSpeed () const;
    bool isIn (const Point2D leftTop, const Point2D rightBottom) const;
    void move (const GLfloat degree);
    bool isCenterOutOfBound () const;

public: // Virtual
    virtual void handlingWhenOutOfBound () { }
    virtual void update ();
    virtual void display () const;

private:
    GLfloat speed;

private:
    Figure* figure;
    Object* parent;
    std::list<Object*> children;

private:
    Rgba color;
    TransformMatrix modelViewMat;
};

#endif