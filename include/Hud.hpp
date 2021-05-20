#ifndef __HUD__
#define __HUD__

#include "core/Object.hpp"
#include "Constants.hpp"

class Hud : public Object {
public:
    Hud(const int playerLives);
    ~Hud();
    virtual void display(const int shadingType, const glm::mat4& viewProjectionMat, const glm::mat4& parentModelViewMat,
                         const DirectionalLightFactors* dFactors, const std::vector<PointLightFactors*>& pFactorsArr, const glm::vec3& viewPos) override;
    virtual void loadShader(unsigned int type, const std::string& vertPath, const std::string& fragPath) override;
    virtual void setShader(unsigned int type, Shader* loadedShader) override;
    void setValue(const uint8_t stage, const int viewMode, bool renderingMode, const int gameMode, const int shadingType, const int playerLives);

private:
    Object* heart;
    std::vector<ModelViewMat> heartMats;
    Object* viewModeTPS;
    Object* viewModeFPS;
    Object* viewMode2D;
    Object* wireOn;
    Object* wireOff;
    Object* allPass;
    Object* allFail;
    Object* phongShading;
    Object* gouraudShading;

private:
    std::string stageText;

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
    glm::vec3 getTranslateVec() const = delete;
    void setSpeed(const float _speed) = delete;
    float getSpeed() const = delete;
    void move(const glm::vec3 directionInModelFrame) = delete;
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