#include "gameplay/GamePlay.hpp"

GamePlay::GamePlay () 
: itemManager(ITEM) {
    player = new Airplane;
    enemy = new Airplane;
    stage = 1;
    enemyRegenIntervalSecs = 3;
    allPassMode = false;
    allFailMode = false;

    airplaneWidth = AIRPLANE_WIDTH;
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
    ui.init(INIT_PLAYER_LIVES);
    player->init(playerInitMat, INIT_PLAYER_LIVES, airplaneWidth, playerSpeed, playerBulletSpeed);
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
    ui.display();
}

/**
 * @brief Handle game frame. It must be called in every frame.
 * @param discreteKeyBuf Discrete keyboard input queue to handle.
 * @param asyncKeyBuf Async keyboard input array to handle. The indices are ASCII code of each key.
 */
void GamePlay::update (std::queue<unsigned char>& discreteKeyBuf, const bool* asyncKeyBuf) {
    handleAsyncKeyInput(asyncKeyBuf);
    handleDiscreteKeyInput(discreteKeyBuf);
    ui.update(stage, !allPassMode && !allFailMode ? " " : (allPassMode ? "All-Pass Mode" : "All-Fail Mode"), player->getLives());
    player->update();
    enemy->update();
    itemManager.update();

    if (!allPassMode && !allFailMode) {
        handleHitNormal(player, enemy);
        handleHitNormal(enemy, player);
    }
    else if (allPassMode && !allFailMode) {
        handleHitInstantKill(player, enemy);
        handleHitDodge(enemy, player);
    }
    else if (!allPassMode && allFailMode) {
        handleHitInstantKill(enemy, player);
    }
    handleAirplaneGotItem(player);

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

/**
 * @brief Handle whether the attacker's bullet hit the target; if hit then subtract a life of the target.
 * @param attacker The object attacking.
 * @param target The object to attack.
 */
void GamePlay::handleHitNormal (Airplane* attacker, Airplane* target) {
    if (!target->isAlive())
        return;
    if (attacker->bulletManager.deactivateObjectWhichIsIn(target->getHitboxLeftTop(), target->getHitboxRightBottom())) {
        target->loseLife();
        if (!target->isAlive()) {
            if (target == player)
                lose();
            if (target == enemy) {
                itemManager.activateObject(enemy->getModelViewMatrix(), ITEM_HEIGHT, Rgba(1.0f, 0.0f, 0.0f), BulletSpeed::SLOW);
                enemyAi.stop();
                if (stage == MAX_STAGE)
                    win();
            }
        }
        if (target == player)
            player->setRandomColor();
    }
}

/**
 * @brief Handle whether the attacker's bullet hit the target; if hit then make target's lives to 0.
 * @param attacker The object attacking.
 * @param target The object to attack.
 */
void GamePlay::handleHitInstantKill (Airplane* attacker, Airplane* target) {
    if (!target->isAlive())
        return;
    if (attacker->bulletManager.deactivateObjectWhichIsIn(target->getHitboxLeftTop(), target->getHitboxRightBottom())) {
        while (target->isAlive())
            target->loseLife();
        if (target == player)
            lose();
        if (target == enemy) {
            itemManager.activateObject(enemy->getModelViewMatrix(), ITEM_HEIGHT, Rgba(1.0f, 0.0f, 0.0f), BulletSpeed::SLOW);
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
void GamePlay::handleHitDodge (Airplane* attacker, Airplane* target) {
    if (!target->isAlive())
        return;
    if (attacker->bulletManager.deactivateObjectWhichIsIn(target->getHitboxLeftTop(), target->getHitboxRightBottom())) {

    }
}

void GamePlay::handleAirplaneGotItem (Airplane* target) {
    if (!target->isAlive())
        return;
    if (itemManager.deactivateObjectWhichIsIn(target->getHitboxLeftTop(), target->getHitboxRightBottom()))
        target->addShotgunBullet();
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
        player->move(180.0f); // left
    else if (!buf[GLUT_KEY_LEFT] && buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
        player->move(90.0f); // up
    else if (!buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
        player->move(0.0f); // right
    else if (!buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && buf[GLUT_KEY_DOWN])
        player->move(270.f); // down
    else if (buf[GLUT_KEY_LEFT] && buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
        player->move(135.0f); 
    else if (!buf[GLUT_KEY_LEFT] && buf[GLUT_KEY_UP] && buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
        player->move(45.0f);
    else if (!buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && buf[GLUT_KEY_RIGHT] && buf[GLUT_KEY_DOWN])
        player->move(315.0f);
    else if (buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && buf[GLUT_KEY_DOWN])
        player->move(225.0f);
}