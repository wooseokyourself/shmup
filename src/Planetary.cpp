#include "Planetary.hpp"

Planetary::Planetary(const std::string aModelPath, const std::string bModelPath, const std::string cModelPath) {
    a = new Object;
    b = new Object;
    c = new Object;
    lightFactors = new PointLightFactors;

    
    a->loadModel(aModelPath);
    b->loadModel(bModelPath);
    c->loadModel(cModelPath);

    aAngle = randomRealNumber(0.025f, 0.5f);
    bAngle = randomRealNumber(0.2f, 2.0f);
    aRotateAxis = glm::vec3(randomRealNumber(-1.0f, 1.0f), randomRealNumber(-1.0f, 1.0f), randomRealNumber(-1.0f, 1.0f));
    bRotateAxis = glm::vec3(randomRealNumber(-1.0f, 1.0f), randomRealNumber(-1.0f, 1.0f), randomRealNumber(-1.0f, 1.0f));

    pushChild(a);
    a->pushChild(b);
    b->pushChild(c);
}

Planetary::~Planetary() {
    delete a;
    delete b;
    delete c;
    delete lightFactors;
}

void Planetary::update() {
    a->setRotate(a->getAngleStack().back() += aAngle, aRotateAxis);
    b->setRotate(b->getAngleStack().back() += bAngle, bRotateAxis);
    lightFactors->lightPosition = c->getWorldPos();
    Object::update();
}

void Planetary::loadShader(unsigned int type, const std::string& vertPath, const std::string& fragPath) {
    Object::loadShader(type, vertPath, fragPath);
    a->setShader(type, shader[type]);
    b->setShader(type, shader[type]);
    c->setShader(type, shader[type]);
}

void Planetary::setShader(unsigned int type, Shader* loadedShader) {
    a->setShader(type, shader[type]);
    b->setShader(type, shader[type]);
    c->setShader(type, shader[type]);
}

void Planetary::setDraw(bool flag) {
    a->setDraw(flag);
    b->setDraw(flag);
    c->setDraw(flag);
}

void Planetary::init(const glm::vec3 pos, const float maxSize) {
    float bSize = maxSize / 3.0f;
    float cSize = bSize / 3.0f;
    
    setTranslate(pos);
    a->setLongestSideTo(maxSize);
    b->setLongestSideTo(bSize);
    c->setLongestSideTo(cSize);

    a->setTranslate(glm::vec3(0.0f, 0.0f, 0.0f));
    b->setTranslate(glm::vec3(0.0f, maxSize, 0.0f));
    c->setTranslate(glm::vec3(0.0f, 0.0f, bSize));

    a->setRotate(aAngle, aRotateAxis);
    b->setRotate(bAngle, bRotateAxis);

    a->setRandomColor();
    b->setRandomColor();
    c->setRandomColor();

    a->setDraw(true);
    b->setDraw(true);
    c->setDraw(true);
}

void Planetary::setLightFactors(const glm::vec4 lightColor, const float ambientStrength, const float specularStrength, const float shininess, 
                                const float constant, const float linear, const float quadratic) {
    lightFactors->color = lightColor;
    lightFactors->ambientStrength = ambientStrength;
    lightFactors->specularStrength = specularStrength;
    lightFactors->shininess = shininess;
    lightFactors->constant = constant;
    lightFactors->linear = linear;
    lightFactors->quadratic = quadratic;
}

PointLightFactors* Planetary::getLightFactors() {
    return lightFactors;
}