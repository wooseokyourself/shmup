#include "Sun.hpp"

Sun::Sun(const glm::vec3 orbitCenter, const float distanceFromCenter, const float anglePerFrame)
: orbitCenter(orbitCenter), radius(distanceFromCenter), angle(anglePerFrame), clockwise(true) {
    lightSource = new Object;
    lightFactors = new DirectionalLightFactors;
    lightSource->setTranslate(glm::vec3(radius, 0.0f, 0.0f));
    pushChild(lightSource);
    setRotate(randomRealNumber(0.0f, 180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}
Sun::~Sun() {
    delete lightSource;
    delete lightFactors;
}
void Sun::update() {
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
    const glm::vec3 lightPos = lightSource->getWorldPos();
    lightFactors->lightDirection = lightPos - orbitCenter;
    Object::update();
}
void Sun::setLightFactors(const glm::vec4 lightColor, const float ambientStrength, const float specularStrength, const float shininess) {
    lightFactors->color = lightColor;
    lightFactors->ambientStrength = ambientStrength;
    lightFactors->specularStrength = specularStrength;
    lightFactors->shininess = shininess;
}
DirectionalLightFactors* Sun::getLightFactors() {
    return lightFactors;
}
