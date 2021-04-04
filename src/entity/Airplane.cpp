#include "entity/Airplane.hpp"

Airplane::Airplane ()
: shotgunBulletNumber(1), bulletSpeed(0.0f), lives(0), lastActivatedTime(0), lastDeactivatedTime(0), updateCount(0), idleMotionToken(false) {
    hitbox = (Rect*)setFigure(FigureType::RECT);
    body = pushChild(FigureType::RECT, FRONT);
    head = body->pushChild(FigureType::TRIANGLE);
    leftArm = body->pushChild(FigureType::BASERECT, BACK);
    rightArm = body->pushChild(FigureType::BASERECT, BACK);
    leftCanon = leftArm->pushChild(FigureType::BASERECT, FRONT);
    rightCanon = rightArm->pushChild(FigureType::BASERECT, FRONT);
}

/**
 * @brief Construct the airplane.
 * @param _lives The number of lives of the airplane.
 */
void Airplane::init (const TransformMatrix& mat, const uint8_t _lives, const GLfloat width, const GLfloat _speed, const GLfloat _bulletSpeed) {
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

    // hitbox (this figure)
    hitbox->setSide(hitBoxWidth, hitBoxHeight); // 3:2
    setMatrix(mat);
    setColor(0.0f, 0.0f, 0.0f, 0.0f);

    // body
    ((Rect*)**body)->setSide(bodyWidth, bodyHeight);
    body->setTranslate(0.0f, (hitBoxHeight - bodyHeight) / 2.0f);
    body->setRandomColor();
    
    // head
    ((Triangle*)**head)->setRadius(headRadius);
    head->setTranslate(0.0f, hitBoxHeight / 2);
    head->setRotate(330.0f);
    head->setRandomColor();

    // left arm
    ((BaseRect*)**leftArm)->setSide(armWidth, armHeight);
    leftArm->setTranslate(-(bodyWidth * 0.34), 0.0f);
    leftArm->setRotate(145.0f);
    leftArm->setRandomColor();

    // right arm
    ((BaseRect*)**rightArm)->setSide(armWidth, armHeight);
    rightArm->setTranslate(bodyWidth * 0.34, 0.0f);
    rightArm->setRotate(-145.0f);
    rightArm->setRandomColor();

    // left canon
    ((BaseRect*)**leftCanon)->setSide(canonWidth, canonHeight);
    leftCanon->setTranslate(0.0f, armHeight);
    leftCanon->setRotate(-145.0f);
    leftCanon->setRandomColor();

    // right canon
    ((BaseRect*)**rightCanon)->setSide(canonWidth, canonHeight);
    rightCanon->setTranslate(0.0f, armHeight);
    rightCanon->setRotate(145.0f);
    rightCanon->setRandomColor();

    lastActivatedTime = glutGet(GLUT_ELAPSED_TIME);
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
void Airplane::fire (ThirdObjectManager* bulletManager) {
    if (!isAlive())
        return;
    const TransformMatrix& mat = getModelViewMatrix();
    GLfloat addingDegree = 15.0f;
    GLfloat bulletDegree = 0.0f;
    if (shotgunBulletNumber % 2 == 0)
        bulletDegree -= (addingDegree / 2.0f);
    for (int i = 0 ; i < shotgunBulletNumber ; i ++) {
        TransformMatrix bulletMat = mat;
        bulletMat.rotate(bulletDegree += (addingDegree * ( (i % 2 == 1) ? i : -i) ));
        bulletManager->activateObject(bulletMat, BULLET_RADIUS, head->getColor(), bulletSpeed);   
    }
}

Point2D Airplane::getHitboxLeftTop () const {
    GLfloat halfWidth = hitbox->getWidth() / 2.0f;
    GLfloat halfHeight = hitbox->getHeight() / 2.0f;
    TransformMatrix mat = getModelViewMatrix();
    return Point2D(mat.tx - halfWidth, mat.ty + halfHeight);
}

Point2D Airplane::getHitboxRightBottom () const {
    GLfloat halfWidth = hitbox->getWidth() / 2.0f;
    GLfloat halfHeight = hitbox->getHeight() / 2.0f;
    TransformMatrix mat = getModelViewMatrix();
    return Point2D(mat.tx + halfWidth, mat.ty - halfHeight);
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

void Airplane::handlingWhenOutOfBound () {
    const TransformMatrix& mat = getModelViewMatrix();
    const Point2D lt = getHitboxLeftTop(), rb = getHitboxRightBottom();
    const GLfloat width = rb.x - lt.x;
    const GLfloat height = lt.y - rb.y;
    if (lt.x < WORLD_BOUND::LEFT)
        setTranslate(WORLD_BOUND::LEFT + width / 2, mat.ty);
    if (rb.x > WORLD_BOUND::RIGHT)
        setTranslate(WORLD_BOUND::RIGHT - width / 2, mat.ty);
    if (lt.y > WORLD_BOUND::UP)
        setTranslate(mat.tx, WORLD_BOUND::UP - height / 2);
    if (rb.y < WORLD_BOUND::DOWN)
        setTranslate(mat.tx, WORLD_BOUND::DOWN + height / 2);
    if (lt.x < WORLD_BOUND::LEFT && rb.y < WORLD_BOUND::DOWN)
        setTranslate(WORLD_BOUND::LEFT + width / 2, WORLD_BOUND::DOWN + height / 2);
    if (lt.x < WORLD_BOUND::LEFT && lt.y > WORLD_BOUND::UP)
        setTranslate(WORLD_BOUND::LEFT + width / 2, WORLD_BOUND::UP - height / 2);
    if (rb.x > WORLD_BOUND::RIGHT && rb.y < WORLD_BOUND::DOWN)
        setTranslate(WORLD_BOUND::RIGHT - width / 2, WORLD_BOUND::DOWN + height / 2);
    if (rb.x > WORLD_BOUND::RIGHT && lt.y > WORLD_BOUND::UP)
        setTranslate(WORLD_BOUND::RIGHT - width / 2, WORLD_BOUND::UP - height / 2);
}

/**
 * @brief Manage all bullets; movement of all bullets, deactivating bullets which is out of bound.
 * This method must be called in all frame.
 * @param bulletDirection The direction of all bullets; LEFT, RIGHT, UP, DOWN, LEFT_UP, UP_RIGHT, RIGHT_DOWN, DOWN_LEFT
 */
void Airplane::update () {
    if (!isAlive())
        return;
    GLfloat degree = idleMotionToken ? 0.2f : -0.2f;
    leftArm->rotate(degree);
    rightArm->rotate(-degree);
    leftCanon->rotate(-degree * 1.2f);
    rightCanon->rotate(degree * 1.2f);
    if (++updateCount > 100) {
        idleMotionToken = !idleMotionToken;
        updateCount = 0;
    }
    Object::update();
}

/**
 * @brief Draw the airplane and its bullets in OpenGL world.
 */
void Airplane::display () const {
    if (isAlive())
        Object::display();
}
