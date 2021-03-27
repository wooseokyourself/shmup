#ifndef __FIGURENODE__
#define __FIGURENODE__

#include "base/core/Figure.hpp"
#include <list>

class FigureNode {
public:
    FigureNode (Figure* _obj);
    ~FigureNode ();
    Figure* operator * ();
    FigureNode* getParent ();
    std::list<FigureNode*>& getChildren ();
    bool isRoot () const;
    bool isExternal () const;
    FigureNode* addChild (Figure* child);
    void addMat (const ModelViewMat2D& mat);

public:
    void display () const;

private:
    Figure* obj;
    FigureNode* parent;
    std::list<FigureNode*> children;
};

#endif