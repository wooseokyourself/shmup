#ifndef __AIRCRAFT__
#define __AIRCRAFT__

#include "core/Object.hpp"
#include "Constants.hpp"
#include "StraightMovingObjectManager.hpp"

class Aircraft : public Object {
public:
    void init (const glm::vec3 _translate,
               const float _angle,
               const glm::vec3 _rotateAxis,
               const glm::vec4 _color, 
               const float maxSideSize,
               const float _speed,
               const int _lives);
    void init (std::string modelPath,
               const glm::vec3 _translate,
               const float _angle,
               const glm::vec3 _rotateAxis,
               const glm::vec4 _color, 
               const float maxSideSize,
               const float _speed,
               const int _lives);
    void loseLife ();
    bool isAlive () const;
    int getLives () const;
    int getLastActivatedTime () const;
    int getLastDeactivatedTime () const;
    void fire(StraightMovingObjectManager* bulletManager, const float bulletMaxSize);
    void addShotgunBullet ();
    void move (const glm::vec3 directionInModelFrame); // override to Object::move()

private:
    void destruct ();

private:
    int shotgunBulletNumber;
    int lives;
    int lastActivatedTime;
    int lastDeactivatedTime;
};

#endif