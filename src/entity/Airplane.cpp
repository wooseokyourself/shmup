#include "entity/Airplane.hpp"

Airplane::Airplane ()
: bulletManager(BULLET), shotgunBulletNumber(1), bulletSpeed(0.0f), lives(0), lastActivatedTime(0), lastDeactivatedTime(0), updateCount(0), idleMotionToken(false) {
    FigureNode * bodyNode, * headNode, * leftArmNode, * rightArmNode, * leftCanonNode, * rightCanonNode;
    base = (Rect*)root->init(RECT);
    bodyNode = root->addChild(RECT);
    headNode = bodyNode->addChild(TRIANGLE);
    leftArmNode = bodyNode->addChild(BASERECT);
    rightArmNode = bodyNode->addChild(BASERECT);
    leftCanonNode = leftArmNode->addChild(BASERECT);
    rightCanonNode = rightArmNode->addChild(BASERECT);

    body = (Rect*)**bodyNode;
    head = (Triangle*)**headNode;
    leftArm = (BaseRect*)**leftArmNode;
    rightArm = (BaseRect*)**rightArmNode;
    leftCanon = (BaseRect*)**leftCanonNode;
    rightCanon = (BaseRect*)**rightCanonNode;
}

Airplane::~Airplane () { }

/**
 * @brief Manage all bullets; movement of all bullets, deactivating bullets which is out of bound.
 * This method must be called in all frame.
 * @param bulletDirection The direction of all bullets; LEFT, RIGHT, UP, DOWN, LEFT_UP, UP_RIGHT, RIGHT_DOWN, DOWN_LEFT
 */
void Airplane::update () {
    bulletManager.update();

    GLfloat degree = idleMotionToken ? 0.2f : -0.2f;
    leftArm->rotate(degree);
    rightArm->rotate(-degree);
    leftCanon->rotate(-degree * 1.2f);
    rightCanon->rotate(degree * 1.2f);
    if (++updateCount > 100) {
        idleMotionToken = !idleMotionToken;
        updateCount = 0;
    }
}

/**
 * @brief Construct the airplane.
 * @param _lives The number of lives of the airplane.
 */
void Airplane::init (const ModelViewMat2D& mat, const uint8_t _lives, const GLfloat width, const GLfloat _speed, const GLfloat _bulletSpeed) {
    if (isAlive())
        return;
    shotgunBulletNumber = 1;
    lives = _lives;
    setSpeed(_speed);
    bulletSpeed = _bulletSpeed;

    GLfloat standard = width; // 0.3f

    // 3:2
    GLfloat hitBoxWidth = standard;
    GLfloat hitBoxHeight = standard * 0.66666f;

    GLfloat bodyWidth = hitBoxWidth * 0.3f;
    GLfloat bodyHeight = hitBoxHeight * 0.75f;

    GLfloat headRadius = bodyWidth / 1.73205f;
    
    GLfloat armWidth = bodyWidth * 0.8f;
    GLfloat armHeight = bodyHeight * 0.9f;

    GLfloat canonWidth = armWidth * 0.9f;
    GLfloat canonHeight = hitBoxHeight * 0.8f;

    base->setSide(hitBoxWidth, hitBoxHeight); // 3:2
    base->setMatrix(mat);
    body->setSide(bodyWidth, bodyHeight);
    body->setTranslate(0.0f, (hitBoxHeight - bodyHeight) / 2.0f);
    body->setRandomColor();
    
    head->setRadius(headRadius);
    head->setTranslate(0.0f, hitBoxHeight / 2);
    head->setRotate(330.0f);

    leftArm->setSide(armWidth, armHeight);
    leftArm->setTranslate(-(bodyWidth * 0.34), 0.0f);
    leftArm->setRotate(145.0f);

    rightArm->setSide(armWidth, armHeight);
    rightArm->setTranslate(bodyWidth * 0.34, 0.0f);
    rightArm->setRotate(-145.0f);

    leftCanon->setSide(canonWidth, canonHeight);
    leftCanon->setTranslate(0.0f, armHeight);
    leftCanon->setRotate(-145.0f);

    rightCanon->setSide(canonWidth, canonHeight);
    rightCanon->setTranslate(0.0f, armHeight);
    rightCanon->setRotate(145.0f);

    base->setColor(Rgba(1.0f, 1.0f, 1.0f, 0.3f));
    body->setRandomColor();
    head->setRandomColor();
    leftArm->setColor(Rgba(1.0f, 0.0f, 0.0f));
    rightArm->setColor(Rgba(0.0f, 1.0f, 0.0f));
    leftCanon->setRandomColor();
    rightCanon->setRandomColor();

    lastActivatedTime = glutGet(GLUT_ELAPSED_TIME);
}

void Airplane::setSpeed (const GLfloat _speed) {
    speed = _speed;
}

void Airplane::setBulletSpeed (const GLfloat _bulletSpeed) {
    bulletSpeed = _bulletSpeed;
}

/**
 * @brief Destruct the airplane.
 */
void Airplane::destruct () {
    std::cout << "Airplane Destructed!" << std::endl;
    lives = 0;
    lastDeactivatedTime = glutGet(GLUT_ELAPSED_TIME);
}

/**
 * @brief Subtract a life of the airplane. If the airplane's life is 0, the airplane will be destructed.
 */
void Airplane::loseLife () {
    if (--lives <= 0)
        destruct();
}

/**
 * @return true if the airplane was not destructed.
 */
bool Airplane::isAlive () const {
    return lives > 0;
}

int Airplane::getLives () const {
    return lives;
}

/**
 * @brief Fire a bullet.
 */
void Airplane::fire () {
    if (!isAlive())
        return;
    const ModelViewMat2D& mat = base->getMatrix();
    GLfloat addingDegree = 15.0f;
    GLfloat bulletDegree = 0.0f;
    if (shotgunBulletNumber % 2 == 0)
        bulletDegree -= (addingDegree / 2.0f);
    for (int i = 0 ; i < shotgunBulletNumber ; i ++) {
        ModelViewMat2D bulletMat = mat;
        bulletMat.rotate(bulletDegree += (addingDegree * ( (i % 2 == 1) ? i : -i) ));
        bulletManager.activateObject(bulletMat, BULLET_RADIUS, Rgba(0.5f, 0.5f, 0.5f), bulletSpeed);   
    }
}

Point2D Airplane::getHitboxLeftTop () const {
    return base->getLeftTop();
}

Point2D Airplane::getHitboxRightBottom () const {
    return base->getRightBottom();
}

ModelViewMat2D Airplane::getModelViewMatrix () const {
    return base->getMatrix();
}

/**
 * @return The last constructed time of the airplane.
 * The time is the elapsed time from the process executed.
 */
int Airplane::getLastActivatedTime () const {
    return lastActivatedTime;
}

/**
 * @return The last destructed time of the airplane.
 * The time is the elapsed time from the process executed.
 */
int Airplane::getLastDeactivatedTime () const {
    return lastDeactivatedTime;
}

void Airplane::setRandomColor () {
    body->setRandomColor();
    head->setRandomColor();
    leftArm->setRandomColor();
    rightArm->setRandomColor();
    leftCanon->setRandomColor();
    rightCanon->setRandomColor();
}

void Airplane::addShotgunBullet () {
    shotgunBulletNumber += 1;
}

/**
 * @brief Draw the airplane and its bullets in OpenGL world.
 */
void Airplane::display () const {
    bulletManager.display();
    if (isAlive())
        root->display();
}
