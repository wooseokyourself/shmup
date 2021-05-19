
#ifndef __DIRECTIONALLIGHT__
#define __DIRECTIONALLIGHT__

#include "core/Object.hpp"

class DirectionalLight : public Object {
public:
    DirectionalLight(const float distanceFromCenter, const float anglePerFrame, const glm::vec4 lightColor)
    : radius(distanceFromCenter), angle(anglePerFrame), clockwise(true) {
        light = new Object;
        light->setColor(lightColor);
        light->setTranslate(glm::vec3(radius, 0.0f, 0.0f));
        pushChild(light);
        setRotate(randomRealNumber(0.0f, 180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    }
    ~DirectionalLight() {
        delete light;
    }
    virtual void update() override {
        const float currentAngle = getAngleStack().back();
        if (currentAngle >= 180.0f)
            clockwise = true;
        else if (currentAngle <= 0.0f)
            clockwise = false;

        float nextAngle = currentAngle;
        if (clockwise)
            nextAngle = nextAngle - angle < 0.0f ? 0.0f : nextAngle - angle;
        else
            nextAngle = nextAngle + angle > 180.0f ? 180.0f : nextAngle + angle;
        setRotate(nextAngle, glm::vec3(0.0f, 0.0f, 1.0f));
        Object::update();
    }
    glm::vec3 getLightPos() {
        const glm::vec4 lightPos = getModelViewMat() * light->getModelViewMat() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        return glm::vec3(lightPos);
    }
    glm::vec4 getColor() const {
        return light->getColor();
    }

private:
    Object* light;
    float radius;
    float angle;
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