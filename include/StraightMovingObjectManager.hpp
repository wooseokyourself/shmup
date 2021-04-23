#ifndef __STRAIGHTMOVINGOBJECTMANAGER__
#define __STRAIGHTMOVINGOBJECTMANAGER__

#include <stack>

#include "core/Object.hpp"
#include "World.hpp"

class Bullet;
class Item;

class StraightMovingObjectManager : public Object {
public:
    StraightMovingObjectManager (const int maxPool, const std::string objectModelPath, const glm::vec3 _objectFront);
    ~StraightMovingObjectManager ();
    virtual void update ();
    virtual void draw ();
    void activateObject (const glm::vec3 translate,
                         const std::vector<float> angleStack,
                         const std::vector<glm::vec3> rotateAxisStack, 
                         const float maxSide, 
                         const glm::vec4 color, 
                         const GLfloat speed);
    size_t getActivatedObjectsNumber () const;
    bool deactivateObjectWhichIsIn (const Object* targetBox);
    void setAutoRotation (const float anglePerFrame, const glm::vec3 axis);

private:
    std::list<Object*> activatedObjects;
    std::stack<Object*> pool;
    glm::vec3 objectFront; // object front in model frame
};

#endif