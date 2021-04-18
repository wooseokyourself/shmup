#ifndef __AIRCRAFT__
#define __AIRCRAFT__

#include "core/Object.hpp"
#include "Constants.hpp"
#include "StraightMovingObjectManager.hpp"

class Aircraft : public Object {
public:
    Aircraft () : Object() { }
    
    virtual void update () {
        Object::update();
    }
    virtual void draw () {
        Object::draw();
    }

public:
    void init (const glm::vec3 _translate,
               const float _angle,
               const glm::vec3 _rotateAxis,
               const glm::vec4 _color, 
               const float maxSideSize,
               const float _speed,
               const int _lives) {
        shotgunBulletNumber = 1;
        setTranslate(_translate);
        setRotate(_angle, _rotateAxis);
        setColor(_color);
        setLongestSideTo(maxSideSize);
        setSpeed(_speed);
        lives = _lives;
        setDraw(true);
        lastActivatedTime = glutGet(GLUT_ELAPSED_TIME);
    }
    void init (std::string modelPath,
               const glm::vec3 _translate,
               const float _angle,
               const glm::vec3 _rotateAxis,
               const glm::vec4 _color, 
               const float maxSideSize,
               const float _speed,
               const int _lives) {
        loadModel(modelPath);
        init(_translate, _angle, _rotateAxis, _color, maxSideSize, _speed, _lives);
    }
    void loseLife () {
        if (--lives <= 0)
            destruct();
    }
    bool isAlive () const {
        return lives > 0;
    }
    int getLives () const {
        return lives;
    }
    int getLastActivatedTime () const {
        return lastActivatedTime;
    }
    int getLastDeactivatedTime () const {
        return lastDeactivatedTime;
    }
    void fire (StraightMovingObjectManager* bulletManager,
               const float bulletMaxSize, 
               const glm::vec4 bulletColor, 
               const float bulletSpeed) {
        if (!isAlive())
            return;
        GLfloat addingDegree = 15.0f;
        GLfloat bulletDegree = 0.0f;
        if (shotgunBulletNumber % 2 == 0)
            bulletDegree -= (addingDegree / 2.0f);
        for (int i = 0 ; i < shotgunBulletNumber ; i ++) {
            float bulletRotateAngle = bulletDegree += (addingDegree * ( (i % 2 == 1) ? i : -i) );
            std::vector<float> aircraftAngleStack = getAngleStack();
            std::vector<glm::vec3> aircraftRotateAxisStack = getRotateAxisStack();
            aircraftAngleStack.push_back(bulletRotateAngle);
            aircraftRotateAxisStack.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
            bulletManager->activateObject(getTranslate(),
                                          aircraftAngleStack, aircraftRotateAxisStack, 
                                          bulletMaxSize, bulletColor, bulletSpeed);   
        }
    }
    void addShotgunBullet () {
        shotgunBulletNumber += 1;
    }
    void move (const glm::vec3 directionInModelFrame) { // override to Object::move()
        glm::vec4 unit = getModelViewMat() * glm::vec4(directionInModelFrame, 0);
        glm::vec3 newTranslate = getTranslate() + glm::vec3(unit / glm::length(glm::vec3(unit)) * getSpeed());
        if (newTranslate.x < -WORLD_LIMIT_ABS)
            newTranslate.x = -WORLD_LIMIT_ABS;
        else if (newTranslate.x > WORLD_LIMIT_ABS)
            newTranslate.x = WORLD_LIMIT_ABS;
        if (newTranslate.y < -WORLD_LIMIT_ABS)
            newTranslate.y = -WORLD_LIMIT_ABS;
        else if (newTranslate.y > WORLD_LIMIT_ABS)
            newTranslate.y = WORLD_LIMIT_ABS;
        if (newTranslate.z < -WORLD_LIMIT_ABS)
            newTranslate.z = -WORLD_LIMIT_ABS;
        else if (newTranslate.z > WORLD_LIMIT_ABS)
            newTranslate.z = WORLD_LIMIT_ABS;
        setTranslate(newTranslate);
    }

private:
    void destruct () {
        std::cout << "Airplane Destructed!" << std::endl;
        lives = 0;
        setDraw(false);
        lastDeactivatedTime = glutGet(GLUT_ELAPSED_TIME);
    }

private:
    int shotgunBulletNumber;
    int lives;
    int lastActivatedTime;
    int lastDeactivatedTime;
};

#endif