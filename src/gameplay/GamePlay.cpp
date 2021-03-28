#include "gameplay/GamePlay.hpp"

GamePlay::GamePlay () 
: itemManager(ITEM) {
    player = new Airplane;
    enemy = new Airplane;
    MAX_STAGE = 5;
    stage = 1;
    enemyRegenIntervalSecs = 3;
    allPassMode = false;
    allFailMode = false;

    airplaneWidth = 0.3f;
    enemyInitMat.setRotate(180.0f);
    playerInitMat.setTranslate(0.0f, -0.5f);
    enemyInitMat.setTranslate(0.0f, 0.5f);
    playerSpeed = AirplaneSpeed::NORMAL;
    playerBulletSpeed = BulletSpeed::FAST;
    enemySpeed = AirplaneSpeed::SLOW;
    enemyBulletSpeed = BulletSpeed::SLOW;
}

GamePlay::~GamePlay () {
    delete player;
    delete enemy;
}

void GamePlay::startGame () {
    int playerLives = 3;
    player->init(playerInitMat, playerLives, airplaneWidth, playerSpeed, playerBulletSpeed);
    enemy->init(enemyInitMat, stage, airplaneWidth, enemySpeed, enemyBulletSpeed);
    enemyAi.start(enemy, DOWN);
}

/**
 * @brief Draw all objects in OpenGL world.
 */
void GamePlay::render () {
    player->display();
    enemy->display();
    itemManager.display();
    displayWall();
    displayStage();
    displayPlayerLives();
}

/**
 * @brief Handle game frame. It must be called in every frame.
 * @param discreteKeyBuf Discrete keyboard input queue to handle.
 * @param asyncKeyBuf Async keyboard input array to handle. The indices are ASCII code of each key.
 */
void GamePlay::update (std::queue<unsigned char>& discreteKeyBuf, const bool* asyncKeyBuf) {
    handleAsyncKeyInput(asyncKeyBuf);
    handleDiscreteKeyInput(discreteKeyBuf);
    player->update();
    enemy->update();
    itemManager.update();

    if (!allPassMode && !allFailMode) {
        checkHitNormal(player, enemy);
        checkHitNormal(enemy, player);
    }
    else if (allPassMode && !allFailMode) {
        checkHitInstantKill(player, enemy);
        checkHitDodge(enemy, player);
    }
    else if (!allPassMode && allFailMode) {
        checkHitInstantKill(enemy, player);
    }

    if (stage > MAX_STAGE)
        win ();
    if (!enemy->isAlive() &&
        (glutGet(GLUT_ELAPSED_TIME) - enemy->getLastDeactivatedTime() >= enemyRegenIntervalSecs * 1000)) {
        enemy->init(enemyInitMat, ++stage, airplaneWidth, enemySpeed, enemyBulletSpeed);
        for (int i = 1 ; i < enemy->getLives() ; i ++)
            enemy->addShotgunBullet();
        enemyAi.start(enemy, DOWN);
    }
}

/**
 * @brief Terminate the process.
 */
void GamePlay::win () {
    std::cout << "Win!" << std::endl;
    enemyAi.stop();
    glutLeaveMainLoop();
}

/**
 * @brief Terminate the process.
 */
void GamePlay::lose () {
    std::cout << "Lose.." << std::endl;
    enemyAi.stop();
    glutLeaveMainLoop();
}

void GamePlay::displayStage () {
    std::string str = "Stage " + std::to_string(stage);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(WORLD_BOUND::RIGHT + 0.05f, 0.9f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2d(0.0f, 0.0f);
    for (int i = 0 ; i < str.size() ; i ++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);

    if (allPassMode || allFailMode) {
        if (allPassMode)
            str = "all pass";
        else if (allFailMode)
            str = "all fail";
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(WORLD_BOUND::RIGHT + 0.05f, 0.8f, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos2d(0.0f, 0.0f);
        for (int i = 0 ; i < str.size() ; i ++)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
    }
}

void GamePlay::displayPlayerLives () {
    for (int i = 0 ; i < player->getLives() ; i ++) {
        Triangle tri;
        tri.setRadius(0.03);
        tri.setColor(1.0f, 0.0f, 0.0f);
        tri.setTranslate(-0.9f + (i * 0.08), -0.9f);
        tri.rotate(90.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        tri.draw();
    }
}

void GamePlay::displayWall () {
    Rect rect;
    rect.setSide(1.0f - WORLD_BOUND::RIGHT, 2.0f);
    GLfloat centerDiffX = (1.0f - WORLD_BOUND::RIGHT) / 2;
    rect.setColor(1.0f, 1.0f, 1.0f);
    rect.setTranslate(WORLD_BOUND::LEFT - centerDiffX, 0.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    rect.draw();
    rect.setTranslate(WORLD_BOUND::RIGHT + centerDiffX, 0.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    rect.draw();
}

/**
 * @brief Handle whether the attacker's bullet hit the target; if hit then subtract a life of the target.
 * @param attacker The object attacking.
 * @param target The object to attack.
 */
void GamePlay::checkHitNormal (Airplane* attacker, Airplane* target) {
    if (!target->isAlive())
        return;
    if (attacker->bulletManager.deactivateObjectWhichIsIn(target->getHitboxLeftTop(), target->getHitboxRightBottom())) {
        target->loseLife();
        if (!target->isAlive()) {
            if (target == player)
                lose();
            if (target == enemy) {
                itemManager.activateObject(enemy->getModelViewMatrix(), 0.15f, Rgba(1.0f, 0.0f, 0.0f), BulletSpeed::SLOW);
                enemyAi.stop();
                if (stage == MAX_STAGE)
                    win();
            }
        }
        if (target == player) { }
            player->setRandomColor();
    }
}

/**
 * @brief Handle whether the attacker's bullet hit the target; if hit then make target's lives to 0.
 * @param attacker The object attacking.
 * @param target The object to attack.
 */
void GamePlay::checkHitInstantKill (Airplane* attacker, Airplane* target) {
    if (!target->isAlive())
        return;
    if (attacker->bulletManager.deactivateObjectWhichIsIn(target->getHitboxLeftTop(), target->getHitboxRightBottom())) {
        while (target->isAlive())
            target->loseLife();
        if (target == player)
            lose();
        if (target == enemy) {
            itemManager.activateObject(enemy->getModelViewMatrix(), 0.15f, Rgba(1.0f, 0.0f, 0.0f), BulletSpeed::SLOW);
            enemyAi.stop();
            if (stage == MAX_STAGE)
                win();
        }
    }
}

/**
 * @brief Handle whether the attacker's bullet hit the target; if hit then do nothing.
 * @param attacker The object attacking.
 * @param target The object to attack.
 */
void GamePlay::checkHitDodge (Airplane* attacker, Airplane* target) {
    if (!target->isAlive())
        return;
    if (attacker->bulletManager.deactivateObjectWhichIsIn(target->getHitboxLeftTop(), target->getHitboxRightBottom())) {

    }
}

/** @brief It deals with keystrokes that don't be allowed continuous input by keyboard push. */
void GamePlay::handleDiscreteKeyInput (std::queue<unsigned char>& discreteKeyBuf) {
    while (!discreteKeyBuf.empty()) {
        unsigned char key = discreteKeyBuf.front();
        discreteKeyBuf.pop();
        switch (key) {
            case ' ':
                if (!allFailMode)
                    player->fire();
                break;
            case 'c':
                if (!allPassMode) {
                    std::cout << "All Pass On" << std::endl;
                    allPassMode = true;
                    allFailMode = false;
                }
                else {
                    std::cout << "All Pass Off" << std::endl;
                    allPassMode = false;
                }
                break;
            case 'f':
                if (!allFailMode) {
                    std::cout << "All Fail On" << std::endl;
                    allFailMode = true;
                    allPassMode = false;
                }
                else {
                    std::cout << "All Fail Off" << std::endl;
                    allFailMode = false;
                }
                break;
        }
    }
}

/** @brief It deals with keystrokes that be allowed continuous input by keyboard push. */
void GamePlay::handleAsyncKeyInput (const bool* asyncKeyBuf) {
    const bool* buf = asyncKeyBuf;
    if (buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
        player->move(LEFT);
    else if (!buf[GLUT_KEY_LEFT] && buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
        player->move(UP);
    else if (!buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
        player->move(RIGHT);
    else if (!buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && buf[GLUT_KEY_DOWN])
        player->move(DOWN);
    else if (buf[GLUT_KEY_LEFT] && buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
        player->move(LEFT_UP);
    else if (!buf[GLUT_KEY_LEFT] && buf[GLUT_KEY_UP] && buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
        player->move(UP_RIGHT);
    else if (!buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && buf[GLUT_KEY_RIGHT] && buf[GLUT_KEY_DOWN])
        player->move(RIGHT_DOWN);
    else if (buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && buf[GLUT_KEY_DOWN])
        player->move(DOWN_LEFT);
}