#include "base/Object.hpp"

Object::Object ()
: speed(0.0f), figure(nullptr), parent(nullptr) { }

Object::~Object () {
    while (!children.empty()) {
        delete children.back();
        children.pop_back();
    }
    if (figure != nullptr)
        delete figure;
}

Figure* Object::setFigure (const int figureType) {
    if (figure != nullptr)
        delete figure;
    switch (figureType) {
        case FigureType::CIRCLE:
            figure = new Circle;
            break;
        case FigureType::RECT:
            figure = new Rect;
            break;
        case FigureType::BASERECT:
            figure = new BaseRect;
            break;
        case FigureType::TRIANGLE:
            figure = new Triangle;
            break;
        case FigureType::TEXT:
            figure = new Text;
            break;
    }
    return figure;
}

Figure* Object::operator * () {
    return figure;
}

Object* Object::pushChild (Object* child) {
    child->parent = this;
    children.push_back(child);
    return child;
}

Object* Object::pushChild (Object* child, const int priority) {
    pushChild(child);
    const GLfloat cmpz = modelViewMat.tz;
    if (priority == FRONT)
        child->translate(0.0f, 0.0f, cmpz >= Window::MIN_DEPTH ? cmpz : cmpz + 1.0f);
    else if (priority == BACK)
        child->translate(0.0f, 0.0f, cmpz <= Window::MAX_DEPTH ? cmpz : cmpz - 1.0f);
    return child;
}

Object* Object::pushChild (const int figureType) {
    Object* child = new Object;
    child->parent = this;
    children.push_back(child);
    switch (figureType) {
        case FigureType::CIRCLE:
            child->setFigure(FigureType::CIRCLE);
            break;
        case FigureType::RECT:
            child->setFigure(FigureType::RECT);
            break;
        case FigureType::BASERECT:
            child->setFigure(FigureType::BASERECT);
            break;
        case FigureType::TRIANGLE:
            child->setFigure(FigureType::TRIANGLE);
            break;
        case FigureType::TEXT:
            child->setFigure(FigureType::TEXT);
            break;
    }
    return child;
}

Object* Object::pushChild (const int figureType, const int priority) {
    Object* child = pushChild(figureType);
    const GLfloat cmpz = modelViewMat.tz;
    if (priority == FRONT)
        child->translate(0.0f, 0.0f, cmpz >= Window::MIN_DEPTH ? cmpz : cmpz + 0.01f);
    else if (priority == BACK)
        child->translate(0.0f, 0.0f, cmpz <= Window::MAX_DEPTH ? cmpz : cmpz - 0.01f);
    return child;
}

void Object::popBackChild () {
    delete children.back();
    children.pop_back();
}

void Object::popFrontChild () {
    delete children.front();
    children.pop_front();
}

std::list<Object*>& Object::getChildren () {
    return children;
}

TransformMatrix Object::getModelViewMatrix () const {
    return modelViewMat;
}

void Object::setMatrix (const TransformMatrix& mat) {
    setTranslate(mat.tx, mat.ty, mat.tz);
    setRotate(mat.degree);
    setScale(mat.sx, mat.sy);
} 

void Object::clearMatrix () {
    setTranslate(0.0f, 0.0f);
    setRotate(0.0f);
    setScale(1.0f, 1.0f);
}

/**
 * @brief Set the x and y of the object.
 * @param p New point of the center point of the object in world space.
 */
void Object::setTranslate (const Point2D p) {
    modelViewMat.setTranslate(p.x, p.y);
}

/**
 * @brief Set the x and y of the object.
 * @param x New x value of the center point of the object in world space.
 * @param y New y value of the center point of the object in world space.
 */
void Object::setTranslate (const GLfloat x, const GLfloat y) {
    modelViewMat.setTranslate(x, y);
}

void Object::setTranslate (const GLfloat x, const GLfloat y, const GLfloat z) {
    modelViewMat.setTranslate(x, y, z);
}

void Object::translate (const Point2D p) {
    modelViewMat.moveTranslate(p.x, p.y);
}

void Object::translate (const GLfloat x, const GLfloat y) {
    modelViewMat.moveTranslate(x, y);
}

void Object::translate (const GLfloat x, const GLfloat y, const GLfloat z) {
    modelViewMat.moveTranslate(x, y, z);
}


void Object::setRotate (const GLfloat degree) {
    modelViewMat.setRotate(degree);
}

void Object::rotate (const GLfloat degree) {
    modelViewMat.rotate(degree);
}

void Object::setScale (const GLfloat x, const GLfloat y) {
    modelViewMat.setScale(x, y);
}

void Object::scale (const GLfloat x, const GLfloat y) {
    modelViewMat.scale(x, y);
}

/**
 * @brief Set color of the object.
 * @param R The R value of the object's color. (0.0 to 1.0)
 * @param G The G value of the object's color. (0.0 to 1.0)
 * @param B The B value of the object's color. (0.0 to 1.0)
 */
void Object::setColor (const GLfloat _R, const GLfloat _G, const GLfloat _B) {
    color.R = _R;
    color.G = _G;
    color.B = _B;
}

void Object::setColor (const GLfloat _R, const GLfloat _G, const GLfloat _B, const GLfloat _A) {
    color.R = _R;
    color.G = _G;
    color.B = _B;
    color.A = _A;
}

/**
 * @brief Set color of the object.
 * @param color The 3-tuple of RGBA value of the object's color. (each value is 0.0 to 1.0)
 */
void Object::setColor (const Rgba _color) {
    color = _color;    
}

Rgba Object::getColor () const {
    return color;
}

/**
 * @brief Set random color of the object.
 */
void Object::setRandomColor () {
    color = Rgba(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
                static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
                static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

void Object::setColorAlpha (const GLfloat _A) {
    color.A = _A;
}

Point2D Object::getWorldPosition () const {
    return Point2D(modelViewMat.tx, modelViewMat.ty);
}

void Object::setSpeed (const GLfloat _speed) {
    speed = _speed;
}

GLfloat Object::getSpeed () const {
    return speed;
}

/**
 * @return true if the center of object is in rectangle.
 * @param leftTop The left-top point of the target range in world space.
 * @param rightBottom The right-bottom point of the target range in world space.
 */
bool Object::isIn (const Point2D leftTop, const Point2D rightBottom) const {
    const GLfloat x = modelViewMat.tx;
    const GLfloat y = modelViewMat.ty;
    if ((leftTop.x <= x && x <= rightBottom.x) && (rightBottom.y <= y && y <= leftTop.y))
        return true;
    return false;
}

void Object::move (const GLfloat degree) {
    GLfloat rad = getRadian(modelViewMat.degree + degree);
    GLfloat x = speed * cos(rad);
    GLfloat y = speed * sin(rad);
    translate(x, y);
    handlingWhenOutOfBound();
}

/**
 * @return true if the object is out of bound.
 */
bool Object::isCenterOutOfBound () const {
    const GLfloat x = modelViewMat.tx;
    const GLfloat y = modelViewMat.ty;
    return x < WORLD_BOUND::LEFT || x > WORLD_BOUND::RIGHT || y < WORLD_BOUND::DOWN || y > WORLD_BOUND::UP;
}

void Object::update () {
    for (Object* child : children)
        child->update();
}

void Object::display () const {
    if (parent == nullptr) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    else
        glPushMatrix();
    glTranslatef(modelViewMat.tx, modelViewMat.ty, modelViewMat.tz);
    glRotatef(modelViewMat.degree, 0.0f, 0.0f, 1.0f);
    glScalef(modelViewMat.sx, modelViewMat.sy, 1.0f);
    if (figure != nullptr) {
        glColor4f(color.R, color.G, color.B, color.A);
        figure->draw();
    }
    for (Object* child : children)
        child->display();
    glPopMatrix();
}