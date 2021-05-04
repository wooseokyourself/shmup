#include "Planetary.hpp"

Planetary::Planetary (const std::string& vertPath, const std::string& fragPath, const std::string aModelPath, const std::string bModelPath, const std::string cModelPath) {
    a = new Object;
    b = new Object;
    c = new Object;
    
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

Planetary::~Planetary () {
    delete a;
    delete b;
    delete c;
}

void Planetary::update () {
    a->setRotate(a->getAngleStack().back() += aAngle, aRotateAxis);
    b->setRotate(b->getAngleStack().back() += bAngle, bRotateAxis);
    Object::update();
}

void Planetary::init (const glm::vec3 pos, const float maxSize) {
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