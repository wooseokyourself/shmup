
#ifndef __PLANETARY__
#define __PLANETARY__

#include "core/Object.hpp"

class Planetary : public Object {
public:
    Planetary(const std::string aModelPath, const std::string bModelPath, const std::string cModelPath);
    ~Planetary();
    virtual void update() override;
    virtual void loadShader(const std::string& vertPath, const std::string& fragPath) override;
    virtual void setShader(Shader* loadedShader) override;
    virtual void setDraw(bool flag) override;
    void init(const glm::vec3 pos, const float maxSize);

private:
    Object* a;
    Object* b;
    Object* c;
    float aAngle;
    float bAngle;
    glm::vec3 aRotateAxis;
    glm::vec3 bRotateAxis;

public:
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
    bool isIn(const glm::vec3 p) const = delete;
    bool isCenterOutOfWorld(const float axisLimitAbs) = delete;
    void setColor(const glm::vec4 _color) = delete;
    void setRandomColor() = delete;
    glm::vec4 getColor() const = delete;
    void assimpToMesh(aiNode* node, const aiScene* scene) = delete;
    void calcBoundingBox(const aiScene* scene) = delete;
    void calculateBoundingBoxForNode(const aiScene* scene, const aiNode* node, aiMatrix4x4* mat, glm::vec3& bbMin, glm::vec3& bbMax) = delete;
};

#endif