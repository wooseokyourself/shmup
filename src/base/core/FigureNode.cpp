#include "base/core/FigureNode.hpp"

FigureNode::FigureNode () { }

FigureNode::~FigureNode () {
    delete obj;
    for (int i = 0 ; i < children.size() ; i ++) {
        FigureNode* child = children.front();
        children.pop_front();
        delete child;
    }
}

void FigureNode::init (const int figure) {
    if (obj != nullptr)
        delete obj;
    switch (figure) {
        case CIRCLE:
            obj = new Circle;
            break;
        case RECT:
            obj = new Rect;
            break;
        case TRIANGLE:
            obj = new Triangle;
            break;
    }
}

Figure* FigureNode::operator * () {
    return obj;
}

bool FigureNode::isRoot () const {
    return (parent == nullptr);
}

bool FigureNode::isExternal () const {
    return children.empty();
}

FigureNode* FigureNode::addChild (const int figure) {
    FigureNode* child = new FigureNode();
    child->parent = this;
    children.push_back(child);
    switch (figure) {
        case CIRCLE:
            child->init(CIRCLE);
            break;
        case RECT:
            child->init(RECT);
            break;
        case TRIANGLE:
            child->init(TRIANGLE);
            break;
    }
    return child;
}

void FigureNode::addMat (const ModelViewMat2D& mat) {
    obj->setMatrix(mat);
}

FigureNode* FigureNode::getParent () {
    return parent;
}

std::list<FigureNode*>& FigureNode::getChildren () {
    return children;
}

void FigureNode::display () const {
    if (isRoot()) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    // draw는 glPushMatrix를 통해 object->mat 을 적용한 뒤
    // (색칠을 포함하여)자신의 버텍스들을 그리고, draw 말미에서 glPushMatrix!
    obj->draw();
    for (FigureNode* child : children)
        child->display();
}
