#include "base/core/FigureNode.hpp"

FigureNode::FigureNode ()
: obj(nullptr), parent(nullptr) { }

FigureNode::~FigureNode () {
    if (obj != nullptr)
        delete obj;
    for (int i = 0 ; i < children.size() ; i ++)
        children.pop_front();
}

Figure* FigureNode::init (const int figure) {
    if (obj != nullptr)
        delete obj;
    switch (figure) {
        case CIRCLE:
            obj = new Circle;
            break;
        case RECT:
            obj = new Rect;
            break;
        case BASERECT:
            obj = new BaseRect;
            break;
        case TRIANGLE:
            obj = new Triangle;
            break;
        case TEXT:
            obj = new Text;
            break;
    }
    return obj;
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
        case BASERECT:
            child->init(BASERECT);
            break;
        case TRIANGLE:
            child->init(TRIANGLE);
            break;
        case TEXT:
            child->init(TEXT);
            break;
    }
    return child;
}

FigureNode* FigureNode::addChild (const int figure, const int priority) {
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
        case BASERECT:
            child->init(BASERECT);
            break;
        case TRIANGLE:
            child->init(TRIANGLE);
            break;
        case TEXT:
            child->init(TEXT);
            break;
    }
    const GLfloat cmpz = obj->getMatrix().tz;
    if (priority == FRONT)
        (**child)->translate(0.0f, 0.0f, cmpz >= Window::MIN_DEPTH ? cmpz : cmpz + 0.01f);
    else if (priority == BACK)
        (**child)->translate(0.0f, 0.0f, cmpz <= Window::MAX_DEPTH ? cmpz : cmpz - 0.01f);
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
    else
        glPushMatrix();
    obj->draw();
    for (FigureNode* child : children)
        child->display();
    glPopMatrix();
}
