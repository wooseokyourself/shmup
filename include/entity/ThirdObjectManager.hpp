#ifndef __THIRDOBJECTMANAGER__
#define __THIRDOBJECTMANAGER__

#include <list>
#include <stack>
#include "entity/Bullet.hpp"
#include "entity/Item.hpp"

enum ObjectType {
    BULLET,
    ITEM
};

class Bullet;
class Item;

class ThirdObjectManager {
public:
    ThirdObjectManager (const int _objectType);
    ~ThirdObjectManager ();
    void activateObject (const ModelViewMat2D& mat, const GLfloat param, const Rgba color, const GLfloat speed);
    void display () const;
    void update (const int bulletDirection);
    size_t getActivatedObjectsNumber () const;
    bool deactivateObjectWhichIsIn (const Point2D leftTop, const Point2D rightBottom);

private:
    int objectType;
    std::list<Object*> activeObjects;
    std::stack<Object*> pool;
};

#endif