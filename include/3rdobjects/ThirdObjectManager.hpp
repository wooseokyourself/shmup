#ifndef __THIRDOBJECTMANAGER__
#define __THIRDOBJECTMANAGER__

#include <list>
#include <stack>
#include "3rdobjects/ThirdObject.hpp"
#include "3rdobjects/Bullet.hpp"
#include "3rdobjects/Item.hpp"

enum ObjectType {
    BULLET,
    ITEM
};

class ThirdObjectManager {
public:
    ThirdObjectManager (const int objectType);
    ~ThirdObjectManager ();
    void activateObject (const ModelViewMat2D& mat, const GLfloat param, const Rgba color, const GLfloat speed);
    void display () const;
    void update (const int bulletDirection);
    size_t getActivatedObjectsNumber () const;
    bool deactivateObjectWhichIsIn (const Point2D leftTop, const Point2D rightBottom);

private:
    std::list<ThirdObject*> activeObjects;
    std::stack<ThirdObject*> pool;
};

#endif