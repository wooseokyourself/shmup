#include "gameplay/GamePlay.hpp"

GamePlay::GamePlay () {
    player = new Airplane (0.0f, -0.5f, 0.3f, 0.1f, 0.05f);
    enemy = new Airplane (0.0f, 0.5f, 0.3f, 0.1f, 0.05f);

    MAX_STAGE = 5;
    stage = 1;
}

GamePlay::~GamePlay () {
    delete player;
    delete enemy;
}

void GamePlay::startGame () {
    player->init(3);
    enemy->init(stage);
}

void GamePlay::render () {
    player->display();
    enemy->display();
}

void GamePlay::update (std::queue<unsigned char>& discreteKeyBuf, const bool* asyncKeyBuf) {
    handleMovement(asyncKeyBuf);
    while (!discreteKeyBuf.empty()) {
        unsigned char key = discreteKeyBuf.front();
        discreteKeyBuf.pop();
        switch (key) {
            case ' ':
                player->fire();
                break;
            case 'c':
                allPass();
                break;
            case 'f':
                allFail();
                break;
        }
    }
    player->update(UP);
    enemy->update(DOWN);
    checkHit(player, enemy);
    checkHit(enemy, player);
    if (stage > MAX_STAGE)
        win ();
    if (!enemy->isActivated())
        spotEnemy();
}

void GamePlay::win () {
    std::cout << "Win!" << std::endl;
}

void GamePlay::lose () {
    std::cout << "Lose.." << std::endl;
}

void GamePlay::allPass () {
    std::cout << "Activate All Pass" << std::endl;
}

void GamePlay::allFail () {
    std::cout << "Activate All Fail" << std::endl;
}

void GamePlay::spotEnemy () {
    if (enemy->isActivated())
        return;
    enemy->init(++stage);
}

void GamePlay::checkHit (Airplane* attacker, Airplane* target) {
    if (!target->isActivated())
        return;
    if (attacker->bulletManager.deactivateBulletIfItsIn(target->getLeftTop(), target->getRightBottom())) {
        std::cout << "Hit!" << std::endl;
        target->loseLife();
    }
}

void GamePlay::handleMovement (const bool* keyBuffer) {
    const bool* buf = keyBuffer;
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