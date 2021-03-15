#include "gameplay/GamePlay.hpp"

GamePlay::GamePlay () {
    player = new Airplane (0.0f, -0.5f, 0.3f, 0.1f, AirplaneSpeed::NORMAL, BulletSpeed::FAST);
    enemy = new Airplane (0.0f, 0.5f, 0.3f, 0.1f, AirplaneSpeed::SLOW, BulletSpeed::SLOW);
    MAX_STAGE = 5;
    stage = 1;
    enemyRegenIntervalSecs = 3;
    allPassMode = false;
    allFailMode = false;
}

GamePlay::~GamePlay () {
    delete player;
    delete enemy;
}

void GamePlay::startGame () {
    player->setRandomColor();
    enemy->setRandomColor();
    player->init(3);
    enemy->init(stage);
    enemyAi.start(enemy, DOWN);
}

/**
 * @brief Draw all objects in OpenGL world.
 */
void GamePlay::render () {
    player->display();
    enemy->display();
}

/**
 * @brief Handle game frame. It must be called in every frame.
 * @param discreteKeyBuf Discrete keyboard input queue to handle.
 * @param asyncKeyBuf Async keyboard input array to handle. The indices are ASCII code of each key.
 */
void GamePlay::update (std::queue<unsigned char>& discreteKeyBuf, const bool* asyncKeyBuf) {
    handleAsyncKeyInput(asyncKeyBuf);
    handleDiscreteKeyInput(discreteKeyBuf);
    player->update(UP);
    enemy->update(DOWN);

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
        enemy->setPosition(0.0f, 0.5f);
        enemy->setRandomColor();
        enemy->init(++stage);
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
void GamePlay::checkHitNormal (Airplane* attacker, Airplane* target) {
    if (!target->isAlive())
        return;
    if (attacker->bulletManager.deactivateBulletWhichIsIn(target->getLeftTop(), target->getRightBottom())) {
        target->loseLife();
        if (!target->isAlive()) {
            if (target == player)
                lose();
            if (target == enemy) {
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
void GamePlay::checkHitInstantKill (Airplane* attacker, Airplane* target) {
    if (!target->isAlive())
        return;
    if (attacker->bulletManager.deactivateBulletWhichIsIn(target->getLeftTop(), target->getRightBottom())) {
        while (target->isAlive())
            target->loseLife();
        if (target == player)
            lose();
        if (target == enemy) {
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
    if (attacker->bulletManager.deactivateBulletWhichIsIn(target->getLeftTop(), target->getRightBottom())) {

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