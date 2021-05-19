#ifndef __STRAIGHTMOVINGOBJECTMANAGER__
#define __STRAIGHTMOVINGOBJECTMANAGER__

#include <stack>

#include "core/Object.hpp"
#include "World.hpp"

class Bullet;
class Item;

class StraightMovingObjectManager : public Object {
public:
    StraightMovingObjectManager(const int maxPool);
    ~StraightMovingObjectManager();
    virtual void update() override;
    virtual void display(const glm::mat4& viewProjectionMat, const glm::mat4& parentModelViewMat) override;
    virtual void display(const glm::mat4& viewProjectionMat, const glm::mat4& parentModelViewMat,
                         const glm::vec3& lightPos, const glm::vec3& viewPos) override;
    void init(const glm::vec3 straightVec, const glm::vec4 color, const float speed);
    void activateObject(const ModelViewMat& initTransform, const float maxSide);
    size_t getActivatedObjectsNumber() const;
    bool deactivateObjectWhichIsIn(Object* targetBox);

private:
    bool isPointOutOfWorld(const glm::vec3& p, const float axisLimitAbs);

private:
    std::list<ModelViewMat*> activatedObjectMat;
    std::stack<ModelViewMat*> pool;
    glm::vec3 objectFront; // object front in model frame

public:
    void translate(const glm::vec3 factors) = delete;
    void setTranslate(const glm::vec3 factors) = delete;
    void rotate(const float angle, const glm::vec3 axis) = delete;
    void setRotate(const float angle, const glm::vec3 axis) = delete;
    void setRotateStack(const std::vector<float> _angleStack, const std::vector<glm::vec3> _rotateAxisStack) = delete;
    void scale(const glm::vec3 factors) = delete;
    void setLongestSideTo(const float len) = delete;
    std::vector<float> getAngleStack() const = delete;
    std::vector<glm::vec3> getRotateAxisStack() const = delete;
    ModelViewMat cloneModelViewObj() const = delete;
    glm::mat4 getModelViewMat() const = delete;
    glm::vec3 getUpVec() const = delete;
    glm::vec3 getFrontVec() const = delete;
    glm::vec3 getWorldPos() const = delete;
    void move(const glm::vec3 directionInModelFrame) = delete;
    bool isIn(const glm::vec3 p) const = delete;
    bool isCenterOutOfWorld(const float axisLimitAbs) = delete;
};

#endif