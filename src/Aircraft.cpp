#include "Aircraft.hpp"

void Aircraft::init(const glm::vec3 _translate,
            const float _angle,
            const glm::vec3 _rotateAxis,
            const float maxSideSize,
            const float _speed,
            const int _lives) {
    shotgunBulletNumber = 1;
    setTranslate(_translate);
    setRotate(_angle, _rotateAxis);
    setLongestSideTo(maxSideSize);
    setSpeed(_speed);
    lives = _lives;
    setDraw(true);
    lastActivatedTime = glutGet(GLUT_ELAPSED_TIME);
}

void Aircraft::init(std::string modelPath,
            const glm::vec3 _translate,
            const float _angle,
            const glm::vec3 _rotateAxis,
            const float maxSideSize,
            const float _speed,
            const int _lives) {
    loadModel(modelPath);
    init(_translate, _angle, _rotateAxis, maxSideSize, _speed, _lives);
}

void Aircraft::loseLife() {
    if (--lives <= 0)
        destruct();
}

bool Aircraft::isAlive() const {
    return lives > 0;
}

int Aircraft::getLives() const {
    return lives;
}

int Aircraft::getLastActivatedTime() const {
    return lastActivatedTime;
}

int Aircraft::getLastDeactivatedTime() const {
    return lastDeactivatedTime;
}

void Aircraft::fire(StraightMovingObjectManager* bulletManager, const float bulletMaxSize) {
    if (!isAlive())
        return;
    float addingDegree = 15.0f;
    float bulletDegree = 0.0f;
    if (shotgunBulletNumber % 2 == 0)
        bulletDegree -= (addingDegree / 2.0f);
    for (int i = 0 ; i < shotgunBulletNumber ; i ++) {
        ModelViewMat bulletInitTransform = modelViewMat;
        float bulletRotateAngle = bulletDegree += (addingDegree * ( (i % 2 == 1) ? i : -i) );
        bulletInitTransform.rotate(bulletRotateAngle, getUpVec());
        bulletManager->activateObject(bulletInitTransform, bulletMaxSize);   
    }
}

void Aircraft::addShotgunBullet() {
    shotgunBulletNumber += 1;
}

void Aircraft::move(const glm::vec3 directionInModelFrame) {
    glm::vec4 unit = getModelViewMat() * glm::vec4(directionInModelFrame, 0);
    glm::vec3 newTranslate = getWorldPos() + glm::vec3(unit / glm::length(glm::vec3(unit)) * getSpeed());
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

void Aircraft::destruct() {
    lives = 0;
    setDraw(false);
    lastDeactivatedTime = glutGet(GLUT_ELAPSED_TIME);
}