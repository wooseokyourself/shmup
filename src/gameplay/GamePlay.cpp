#include "gameplay/GamePlay.hpp"

GamePlay::GamePlay () {
    gameworld = new Object;
    ui = new Ui(INIT_PLAYER_LIVES);
    player = new Airplane;
    enemy = new Airplane;
    playerBulletManager = new ThirdObjectManager(BULLET);
    enemyBulletManager = new ThirdObjectManager(BULLET);
    itemManager = new ThirdObjectManager(ITEM);
    planetaryA = new Planetary;
    planetaryB = new Planetary;

    gameworld->pushChild(ui, FRONT);
    gameworld->pushChild(planetaryA, BACK);
    gameworld->pushChild(planetaryB, BACK);
    gameworld->pushChild(player);
    gameworld->pushChild(enemy);
    gameworld->pushChild(playerBulletManager);
    gameworld->pushChild(enemyBulletManager);
    gameworld->pushChild(itemManager);
    
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
    delete gameworld;
}

void GamePlay::startGame () {
    ui->init();
    player->init(playerInitMat, INIT_PLAYER_LIVES, airplaneWidth, playerSpeed, playerBulletSpeed);
    enemy->init(enemyInitMat, stage, airplaneWidth, enemySpeed, enemyBulletSpeed);
    enemyAi.start(enemy, enemyBulletManager);

    TransformMatrix mat;
    mat.setTranslate(randomRealNumber(-1.0f, -0.3f), randomRealNumber(-1.0f, -0.3f));
    planetaryA->init(mat, randomRealNumber(0.05f, 0.3f));
    mat.setTranslate(randomRealNumber(0.3f, 1.0f), randomRealNumber(0.3f, 1.0f));
    planetaryB->init(mat, randomRealNumber(0.05f, 0.3f));
}

void GamePlay::render () {
    gameworld->display();
}

void GamePlay::update (std::queue<unsigned char>& discreteKeyBuf, const bool* asyncKeyBuf) {
    handleAsyncKeyInput(asyncKeyBuf);
    handleDiscreteKeyInput(discreteKeyBuf);
    ui->setValue(stage, !allPassMode && !allFailMode ? " " : (allPassMode ? "All-Pass Mode" : "All-Fail Mode"), player->getLives());
    gameworld->update();

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
        enemyAi.start(enemy, enemyBulletManager);
    }
}

void GamePlay::win () {
    std::cout << "Win!" << std::endl;
    enemyAi.stop();
    glutLeaveMainLoop();
}

void GamePlay::lose () {
    std::cout << "Lose.." << std::endl;
    enemyAi.stop();
    glutLeaveMainLoop();
}

void GamePlay::handleHitNormal (Airplane* attacker, Airplane* target) {
    if (!target->isAlive())
        return;
    ThirdObjectManager* attackerBulletManager = (attacker == player ? playerBulletManager : enemyBulletManager);
    if (attackerBulletManager->deactivateObjectWhichIsIn(target->getHitboxLeftTop(), target->getHitboxRightBottom())) {
        target->loseLife();
        if (!target->isAlive()) {
            if (target == player)
                lose();
            if (target == enemy) {
                itemManager->activateObject(enemy->getModelViewMatrix(), ITEM_HEIGHT, Rgba(1.0f, 0.0f, 0.0f), BulletSpeed::SLOW);
                enemyAi.stop();
                if (stage == MAX_STAGE)
                    win();
            }
        }
        if (target == player)
            player->setRandomColor();
    }
}

void GamePlay::handleHitInstantKill (Airplane* attacker, Airplane* target) {
    if (!target->isAlive())
        return;
    ThirdObjectManager* attackerBulletManager = (attacker == player ? playerBulletManager : enemyBulletManager);
    if (attackerBulletManager->deactivateObjectWhichIsIn(target->getHitboxLeftTop(), target->getHitboxRightBottom())) {
        TransformMatrix attackerMat = attacker->getModelViewMatrix();
        TransformMatrix targetMat = target->getModelViewMatrix();
        Point2D attackerLt = attacker->getHitboxLeftTop(), attackerRb = attacker->getHitboxRightBottom(), targetLt = target->getHitboxLeftTop(), targetRb = target->getHitboxRightBottom();
        while (target->isAlive())
            target->loseLife();
        if (target == player)
            lose();
        if (target == enemy) {
            itemManager->activateObject(enemy->getModelViewMatrix(), ITEM_HEIGHT, Rgba(1.0f, 0.0f, 0.0f), BulletSpeed::SLOW);
            enemyAi.stop();
            if (stage == MAX_STAGE)
                win();
        }
    }
}

void GamePlay::handleHitDodge (Airplane* attacker, Airplane* target) {
    if (!target->isAlive())
        return;
    ThirdObjectManager* attackerBulletManager = (attacker == player ? playerBulletManager : enemyBulletManager);
    if (attackerBulletManager->deactivateObjectWhichIsIn(target->getHitboxLeftTop(), target->getHitboxRightBottom())) {

    }
}

void GamePlay::handleAirplaneGotItem (Airplane* target) {
    if (!target->isAlive())
        return;
    if (itemManager->deactivateObjectWhichIsIn(target->getHitboxLeftTop(), target->getHitboxRightBottom()))
        target->addShotgunBullet();
}

void GamePlay::handleDiscreteKeyInput (std::queue<unsigned char>& discreteKeyBuf) {
    while (!discreteKeyBuf.empty()) {
        unsigned char key = discreteKeyBuf.front();
        discreteKeyBuf.pop();
        switch (key) {
            case ' ':
                if (!allFailMode)
                    player->fire(playerBulletManager);
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