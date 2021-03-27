#include "base/core/FigureNode.hpp"

FigureNode::FigureNode (Figure* _obj)
: obj(_obj) {
    parent = nullptr;
}

FigureNode::~FigureNode () {
    delete obj;
    for (int i = 0 ; i < children.size() ; i ++) {
        FigureNode* child = children.front();
        children.pop_front();
        delete child;
    }
}

Figure* FigureNode::operator * () {
    return obj;
}

FigureNode* FigureNode::getParent () {
    return parent;
}

std::list<FigureNode*>& FigureNode::getChildren () {
    return children;
}

bool FigureNode::isRoot () const {
    return (parent == nullptr);
}

bool FigureNode::isExternal () const {
    return children.empty();
}

FigureNode* FigureNode::addChild (Figure* child) {
    FigureNode* node = new FigureNode(child);
    node->parent = this;
    children.push_back(node);
    return node;
}

void FigureNode::addMat (const ModelViewMat2D& mat) {
    obj->setMatrix(mat);
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
