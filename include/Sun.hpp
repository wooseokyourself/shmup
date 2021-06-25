
#ifndef __SUN__
#define __SUN__

#include "core/Object.hpp"

class Sun : public Object {
public:
    Sun(const glm::vec3 orbitCenter, const float distanceFromCenter, const float anglePerFrame);
    ~Sun();
    virtual void update() override;
    void setLightFactors(const glm::vec4 lightColor, const float ambientStrength, const float specularStrength, const float shininess);
    DirectionalLightFactors* getLightFactors();

private:
    Object* lightSource;
    DirectionalLightFactors* lightFactors;
    float radius;
    float angle;
    glm::vec3 orbitCenter;
    bool clockwise;

public:
    void scale(const glm::vec3 factors) = delete;
    void setLongestSideTo(const float len) = delete;
    std::vector<glm::vec3> getRotateAxisStack() const = delete;
    void loadModel(const std::string& path) = delete;
    ModelViewMat cloneModelViewObj() const = delete;
    void setModelViewMat(const ModelViewMat& _mat) = delete;
    glm::vec3 getUpVec() const = delete;
    glm::vec3 getFrontVec() const = delete;
    void setSpeed(const float _speed) = delete;
    float getSpeed() const = delete;
    bool isIn(const glm::vec3 p) const = delete;
    bool isCenterOutOfWorld(const float axisLimitAbs) = delete;
    void setColor(const glm::vec4 _color) = delete;
    void setRandomColor() = delete;
    void assimpToMesh(aiNode* node, const aiScene* scene) = delete;
    void calcBoundingBox(const aiScene* scene) = delete;
    void calculateBoundingBoxForNode(const aiScene* scene, const aiNode* node, aiMatrix4x4* mat, glm::vec3& bbMin, glm::vec3& bbMax) = delete;
};

#endif