#ifndef __AIRCRAFT__
#define __AIRCRAFT__

#include "core/Object.hpp"

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
               const glm::vec3 _rotate,
               const glm::vec3 _scale,
               const int _speed,
               const int _lives,
               const int _bulletSpeed) {
        shotgunBulletNumber = 1;
        lives = _lives;
        setSpeed(_speed);
        bulletSpeed = _bulletSpeed;
        lastActivatedTime = glutGet(GLUT_ELAPSED_TIME);
    }
    void init (std::string modelPath,
               const glm::vec3 _translate,
               const float _angle,
               const glm::vec3 _rotate,
               const glm::vec3 _scale,
               const int _speed,
               const int _lives,
               const int _bulletSpeed) {
        loadModel(modelPath);
        init(_translate, _angle, _rotate, _scale, _speed, _lives, _bulletSpeed);
    }
    void setBulletSpeed (const float _bulletSpeed) {
        bulletSpeed = _bulletSpeed;
    }
    void destruct () {
        std::cout << "Airplane Destructed!" << std::endl;
        lives = 0;
        lastDeactivatedTime = glutGet(GLUT_ELAPSED_TIME);
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
    /*
    void fire (void* bulletManager) {
        if (!isAlive())
            return;
        GLfloat addingDegree = 15.0f;
        GLfloat bulletDegree = 0.0f;
        if (shotgunBulletNumber % 2 == 0)
            bulletDegree -= (addingDegree / 2.0f);
        // 만약 비행기가 위아래로 각도조절이 가능하다면 꽤 복잡해질듯하다..
        for (int i = 0 ; i < shotgunBulletNumber ; i ++) {
            float bulletRotateAngle = bulletDegree += (addingDegree * ( (i % 2 == 1) ? i : -i) );
            bulletManager->activateObject(bulletRotateAngle, 
                                          glm::vec3(0.0f, 1.0f, 0.0f),
                                          bulletSpeed);   
        }
    }
    */

private:
    int shotgunBulletNumber;
    float bulletSpeed;
    int lives;
    int lastActivatedTime;
    int lastDeactivatedTime;

private:
    int updateCount;
};

#endif