
#ifndef __PLANETARY__
#define __PLANETARY__

#include "core/Object.hpp"

class Planetary : public Object {
public:
    Planetary (const std::string aModelPath, const std::string bModelPath, const std::string cModelPath) {
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
    ~Planetary () {
        delete a;
        delete b;
        delete c;
    }
    void init (const glm::vec3 pos, const float maxSize) {
        float bSize = maxSize * 10.0f;
        float cSize = bSize * 5.0f;
        
        setTranslate(pos);
        a->setLongestSideTo(maxSize);
        b->setLongestSideTo(bSize);
        c->setLongestSideTo(cSize);

        a->setTranslate(0.0f, 0.0f, 0.0f);
        b->setTranslate(0.0f, bSize * 2.0f, 0.0f);
        c->setTranslate(0.0f, 0.0f, cSize * 2.0f);

        a->setRotate(aAngle, aRotateAxis);
        b->setRotate(bAngle, bRotateAxis);

        a->setRandomColor();
        b->setRandomColor();
        c->setRandomColor();

        a->setDraw(true);
        b->setDraw(true);
        c->setDraw(true);
    }

public:
    virtual void update () {
        a->setRotate(a->getAngleStack().back() += aAngle, aRotateAxis);
        b->setRotate(b->getAngleStack().back() += bAngle, bRotateAxis);
        Object::update();
    }

private:
    Object* a;
    Object* b;
    Object* c;
    float aAngle;
    float bAngle;
    glm::vec3 aRotateAxis;
    glm::vec3 bRotateAxis;
};

#endif