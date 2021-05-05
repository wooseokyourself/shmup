#ifndef __STRAIGHTMOVINGOBJECTMANAGER__
#define __STRAIGHTMOVINGOBJECTMANAGER__

#include <stack>

#include "core/Object.hpp"
#include "World.hpp"

class Bullet;
class Item;

class StraightMovingObjectManager : public Object {
public:
    StraightMovingObjectManager (const int maxPool);
    ~StraightMovingObjectManager ();
    virtual void update ();
    virtual void display (const glm::mat4& projection, const glm::mat4& lookAt, const glm::mat4& prevMat);
    void init(const glm::vec3 straightVec, const glm::vec4 color, const float speed);
    void activateObject (const ModelViewMat& initTransform, const float maxSide);
    size_t getActivatedObjectsNumber () const;
    bool deactivateObjectWhichIsIn (const Object* targetBox);

private:
    bool isPointOutOfWorld(const glm::vec3& p, const float axisLimitAbs);

private:
    std::list<ModelViewMat*> activatedObjectMat;
    std::stack<ModelViewMat*> pool;
    glm::vec3 objectFront; // object front in model frame
};

#endif