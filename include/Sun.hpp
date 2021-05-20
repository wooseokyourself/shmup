
#ifndef __SUN__
#define __SUN__

#include "core/Object.hpp"

class Sun : public Object {
public:
    Sun(const float distanceFromCenter, const float anglePerFrame,
        const glm::vec4 lightColor, const float ambientStrength, const float specularStrength, const float shininess)
    : radius(distanceFromCenter), angle(anglePerFrame), clockwise(true) {
        lightFactors.color = lightColor;
        lightFactors.ambientStrength = ambientStrength; // 0.01f;
        lightFactors.specularStrength = specularStrength; // 0.5f;
        lightFactors.shininess = shininess; // 32.0f 
        lightSource = new Object;
        lightSource->setTranslate(glm::vec3(radius, 0.0f, 0.0f));
        pushChild(lightSource);
        setRotate(randomRealNumber(0.0f, 180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    }
    ~Sun() {
        delete lightSource;
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
    DirectionalLightFactors getFactors(const glm::vec3& orbitCenter) {
        const glm::vec3 lightPos = getModelViewMat() * lightSource->getModelViewMat() * glm::vec3(0.0f, 0.0f, 0.0f);
        lightFactors.lightDirection = lightPos - orbitCenter;
        return lightFactors;
    }
    glm::vec4 getColor() const {
        return lightFactors.color;
    }

private:
    DirectionalLightFactors lightFactors;
    Object* lightSource;
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