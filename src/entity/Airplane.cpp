#include "entity/Airplane.hpp"

Airplane::Airplane () :
bulletManager(BULLET), bulletSpeed(0.0f), lives(0), lastActivatedTime(0), lastDeactivatedTime(0) {
    base = (Rect*)root->init(RECT);
    FigureNode* bodyNode = root->addChild(RECT);
    body = (Rect*)**bodyNode;
    FigureNode* headNode = bodyNode->addChild(TRIANGLE);
    head = (Triangle*)**headNode;
}

Airplane::~Airplane () { }

/**
 * @brief Manage all bullets; movement of all bullets, deactivating bullets which is out of bound.
 * This method must be called in all frame.
 * @param bulletDirection The direction of all bullets; LEFT, RIGHT, UP, DOWN, LEFT_UP, UP_RIGHT, RIGHT_DOWN, DOWN_LEFT
 */
void Airplane::update (const int bulletDirection) {
    bulletManager.update(bulletDirection);
    // 여기에서 model에 움직임 적용해줘야함
}

/**
 * @brief Construct the airplane.
 * @param _lives The number of lives of the airplane.
 */
void Airplane::init (const ModelViewMat2D& mat, const uint8_t _lives, const GLfloat width, const GLfloat _speed, const GLfloat _bulletSpeed) {
    if (isAlive())
        return;
    lives = _lives;
    setSpeed(_speed);
    bulletSpeed = _bulletSpeed;

    GLfloat standard = width; // 0.3f

    // 3:2
    GLfloat hitBoxWidth = standard;
    GLfloat hitBoxHeight = standard * 0.66666f;

    GLfloat bodyWidth = hitBoxWidth * 0.25f;
    GLfloat bodyHeight = hitBoxHeight * 0.75f;

    GLfloat headRadius = bodyWidth / 1.73205f;

    base->setSide(hitBoxWidth, hitBoxHeight); // 3:2
    base->setMatrix(mat);
    body->setSide(bodyWidth, bodyHeight);
    body->setTranslate(0.0f, (hitBoxHeight - bodyHeight) / 2.0f);
    body->setRandomColor();
    head->setRadius(headRadius);
    head->setTranslate(0.0f, hitBoxHeight / 2);
    head->setRotate(330.0f);

    base->setColor(Rgba(1.0f, 1.0f, 1.0f, 0.3f));
    body->setRandomColor();
    head->setRandomColor();

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
    if (isAlive())
        bulletManager.activateObject(base->getMatrix(), 0.025, Rgba(0.5f, 0.5f, 0.5f), bulletSpeed);
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

/**
 * @brief Draw the airplane and its bullets in OpenGL world.
 */
void Airplane::display () const {
    bulletManager.display();
    if (isAlive())
        root->display();
}
