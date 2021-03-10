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
    player->setColor(1.0f, 0.0f, 0.0f);
    enemy->setColor(0.0f, 0.0f, 0.0f);
    player->init(3);
    enemy->init(stage);
    enemyAi.start(enemy, DOWN);
}

void GamePlay::render () {
    player->display();
    enemy->display();
}

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
        enemy->init(++stage);
        switch (stage) {
            case (2):
                enemy->setColor(0.0f, 0.0f, 1.0f);
                break;
            case (3):
                enemy->setColor(0.0f, 1.0f, 0.0f);
                break;
            case (4):
                enemy->setColor(0.0f, 1.0f, 1.0f);
                break;
            case (5):
                enemy->setColor(1.0f, 0.0f, 0.0f);
                break;
        }
        enemyAi.start(enemy, DOWN);
    }
}

void GamePlay::win () {
    std::cout << "Win!" << std::endl;
}

void GamePlay::lose () {
    std::cout << "Lose.." << std::endl;
}

void GamePlay::checkHitNormal (Airplane* attacker, Airplane* target) {
    if (!target->isAlive())
        return;
    if (attacker->bulletManager.deactivateBulletIfItsIn(target->getLeftTop(), target->getRightBottom())) {
        target->loseLife();
        if (!target->isAlive()) {
            target->destruct();
            if (target == enemy)
                enemyAi.stop();
        }
    }
}

void GamePlay::checkHitInstantKill (Airplane* attacker, Airplane* target) {
    if (!target->isAlive())
        return;
    if (attacker->bulletManager.deactivateBulletIfItsIn(target->getLeftTop(), target->getRightBottom())) {
        target->destruct();
        if (target == enemy)
            enemyAi.stop();
    }
}

void GamePlay::checkHitDodge (Airplane* attacker, Airplane* target) {
    if (!target->isAlive())
        return;
    if (attacker->bulletManager.deactivateBulletIfItsIn(target->getLeftTop(), target->getRightBottom())) {

    }
}

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
                    allPassMode = true;
                    allFailMode = false;
                }
                else
                    allPassMode = false;
                break;
            case 'f':
                if (!allFailMode) {
                    allFailMode = true;
                    allPassMode = false;
                }
                else
                    allFailMode = false;
                break;
        }
    }
}

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