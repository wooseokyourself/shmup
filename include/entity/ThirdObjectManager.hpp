#ifndef __THIRDOBJECTMANAGER__
#define __THIRDOBJECTMANAGER__

#include <stack>
#include "base/Object.hpp"
#include "entity/Bullet.hpp"
#include "entity/Item.hpp"

enum ObjectType {
    BULLET,
    ITEM
};

class Bullet;
class Item;

class ThirdObjectManager : public Object {
public:
    ThirdObjectManager (const int _objectType);
    ~ThirdObjectManager ();
    void activateObject (const TransformMatrix& mat, const GLfloat param, const Rgba color, const GLfloat speed);
    size_t getActivatedObjectsNumber () const;
    bool deactivateObjectWhichIsIn (const Point2D leftTop, const Point2D rightBottom);

public:
    virtual void update ();
    virtual void display () const;

private:
    int objectType;
    std::list<Object*> activeObjects;
    std::stack<Object*> pool;
};

#endif