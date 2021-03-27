#include "entity/Airplane.hpp"

Airplane::Airplane () {
    // Construct components
    Rect* hitBox = new Rect;
    Rect* body = new Rect;
    Triangle* head = new Triangle;
    // Rect* leftArm = new Rect;
    // Rect* rightArm = new Rect;
    // Rect* leftCanon = new Rect;
    // Rect* rightCanon = new Rect;

    GLfloat base = 0.3f;

    // 3:2
    GLfloat hitBoxWidth = base;
    GLfloat hitBoxHeight = base * 0.333333f;
    
    GLfloat bodyWidth = hitBoxWidth * 0.25f;
    GLfloat bodyHeight = hitBoxHeight * 0.75f;

    GLfloat headRadius = bodyWidth / 2.0f * 1.73205f; // 2*sqrt(3)

    hitBox->setSide(hitBoxWidth, hitBoxHeight); // 3:2
    hitBox->setPosition(0.0f, 0.0f);
    body->setSide(bodyWidth, bodyHeight);
    body->setPosition(0.0f, hitBoxHeight - bodyHeight);
    body->setRandomColor();
    head->setRadius(headRadius);
    head->setRotate(330.0f); // 이는 플레이어의 비행기각도, 적은 달라야함
    head->setPosition(0.0f, (hitBoxHeight / 2) + (headRadius / 2));
    // ...

    // Construct a model tree
    FigureNode *root, *bodyNode, *leftArmNode, *rightArmNode;
    root = new FigureNode(hitBox);
    bodyNode = root->addChild(body);
    bodyNode->addChild(head);
    // leftArmNode = bodyNode->addChild(leftArm);
    // rightArmNode = bodyNode->addChild(rightArm);
    // leftArmNode->addChild(leftCanon);
    // rightArmNode->addChild(rightCanon);
    model = root;
}

Airplane::~Airplane () {
    delete model;
}

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
void Airplane::init (const Point2D p, const uint8_t _lives) {
    if (isAlive())
        return;
    (**model)->setPosition(p);
    lives = _lives;
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
        bulletManager.activateObject(mat, 0.025, Rgba(color.R + 0.15f, color.G + 0.15f, color.B + 0.15f), bulletSpeed);
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
void Airplane::display () {
    bulletManager.display();
    if (isAlive())
        Rect::display();
}
