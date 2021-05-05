#ifndef __WORLD__
#define __WORLD__

#include "core/Object.hpp"
#include "Constants.hpp"

class World : public Object {
public:
    World();

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
    void loadModel(const std::string& path) = delete;
    ModelViewMat cloneModelViewObj() const = delete;
    void setModelViewMat(const ModelViewMat& _mat) = delete;
    glm::mat4 getModelViewMat() const = delete;
    glm::vec3 getUpVec() const = delete;
    glm::vec3 getFrontVec() const = delete;
    void setSpeed(const float _speed) = delete;
    float getSpeed() const = delete;
    void move(const glm::vec3 directionInModelFrame) = delete;
    void assimpToMesh(aiNode* node, const aiScene* scene) = delete;
    void calcBoundingBox(const aiScene* scene) = delete;
    void calculateBoundingBoxForNode(const aiScene* scene, const aiNode* node, aiMatrix4x4* mat, glm::vec3& bbMin, glm::vec3& bbMax) = delete;
};

#endif