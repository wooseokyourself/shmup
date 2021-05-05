#ifndef __HUD__
#define __HUD__

#include "core/Object.hpp"
#include "Constants.hpp"

class Hud : public Object {
public:
    virtual void display (const glm::mat4& projection, const glm::mat4& lookAt, const glm::mat4& prevMat);
    void init (const int playerLives);
    void setValue (const uint8_t stage, const int viewMode, bool renderingMode, const int gameMode, const int playerLives);
    void setWireframe (bool flag); // override to Object::setWireframe()

private:
    void drawText ();

private:
    std::string stageText;
    std::string viewModeText;
    std::string renderingModeText;
    std::string gameModeText;
    std::vector<Object*> heartPtrs;

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
    glm::mat4 getModelViewMat() const = delete;
    glm::vec3 getUpVec() const = delete;
    glm::vec3 getFrontVec() const = delete;
    glm::vec3 getWorldPos() const = delete;
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