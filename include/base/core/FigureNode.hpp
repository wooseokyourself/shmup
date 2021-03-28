#ifndef __FIGURENODE__
#define __FIGURENODE__

#include "base/core/Figure.hpp"
#include "base/core/Circle.hpp"
#include "base/core/Rect.hpp"
#include "base/core/BaseRect.hpp"
#include "base/core/Triangle.hpp"
#include <list>

enum Figures {
    CIRCLE,
    RECT,
    BASERECT,
    TRIANGLE
};

class FigureNode {
public:
    FigureNode ();
    ~FigureNode ();
    Figure* init (const int figure);
    Figure* operator * ();
    bool isRoot () const;
    bool isExternal () const;
    FigureNode* addChild (const int figure);
    void addMat (const ModelViewMat2D& mat);
    FigureNode* getParent ();
    std::list<FigureNode*>& getChildren ();

public:
    void display () const;

private:
    Figure* obj;
    FigureNode* parent;
    std::list<FigureNode*> children;
};

#endif