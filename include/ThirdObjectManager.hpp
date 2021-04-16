#ifndef __THIRDOBJECTMANAGER__
#define __THIRDOBJECTMANAGER__

#include <stack>

#include "core/Object.hpp"
#include "Bullet.hpp"
#include "Item.hpp"

class Bullet;
class Item;

class ThirdObjectManager : public Object {
public:
    ThirdObjectManager (const int _objectType);
    ~ThirdObjectManager ();
    void activateObject (const glm::vec3 translate,
                         const glm::vec3 rotate,
                         const glm::vec3 angle,
                         const glm::vec4 color, 
                         const GLfloat speed,
                         const GLfloat param);
    size_t getActivatedObjectsNumber () const;
    // bool deactivateObjectWhichIsIn (const Point2D leftTop, const Point2D rightBottom);

public:
    virtual void update ();
    virtual void display () const;

private:
    int objectType;
    std::list<Object*> activeObjects;
    std::stack<Object*> pool;
};

#endif