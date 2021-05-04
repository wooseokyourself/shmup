#include "GamePlay.hpp"

GamePlay::GamePlay () : viewMode(0) {
    cout << "start gameplay constructor" << endl;

    stage = 1;
    gameMode = GAMEMODE_NONE;
    viewMode = VIEWMODE_TPS;
    renderingMode = true;

    perspectiveSceneRoot = new World;
    player = new Aircraft;
    enemy = new Aircraft;
    playerBulletManager = new StraightMovingObjectManager("shader/vertex.vert", "shader/fragment.frag", 1, "assets/models/sphere.obj", glm::vec3(0.0f, 0.0f, 1.0f));
    cout << " playerBulletManager allocated done" << endl;
    enemyBulletManager = new StraightMovingObjectManager("shader/vertex.vert", "shader/fragment.frag", 1, "assets/models/sphere.obj", glm::vec3(0.0f, 0.0f, 1.0f));
    cout << " enemyBulletManager allocated done" << endl;
    itemManager = new StraightMovingObjectManager("shader/vertex.vert", "shader/fragment.frag", 1, "assets/models/ammo_crate.obj", glm::vec3(0.0f, 0.0f, 1.0f));
    cout << " itemManager allocated done" << endl;
    // planetaryA = new Planetary("assets/models/sphere.obj", "assets/models/sphere.obj", "assets/models/sphere.obj");
    // planetaryB = new Planetary("assets/models/sphere.obj", "assets/models/sphere.obj", "assets/models/sphere.obj");

    // hud = new Hud;

    cout << "allocated done" << endl;

    player->loadShader("shader/vertex.vert", "shader/fragment.frag");
    enemy->loadShader("shader/vertex.vert", "shader/fragment.frag");
    // planetaryA->loadShader("shader/vertex.vert", "shader/fragment.frag");
    // planetaryB->loadShader("shader/vertex.vert", "shader/fragment.frag");

    player->loadModel("assets/models/player.obj");
    enemy->loadModel("assets/models/ebm314.obj");

    cout << "shader loading done" << endl;

    // perspectiveSceneRoot->pushChild(planetaryA);
    // perspectiveSceneRoot->pushChild(planetaryB);
    perspectiveSceneRoot->pushChild(player);
    perspectiveSceneRoot->pushChild(enemy);
    perspectiveSceneRoot->pushChild(playerBulletManager);
    perspectiveSceneRoot->pushChild(enemyBulletManager);
    perspectiveSceneRoot->pushChild(itemManager);

    const float base = WINDOW_HEIGHT < WINDOW_WIDTH ? WINDOW_HEIGHT : WINDOW_WIDTH;
    const float widthset = WINDOW_WIDTH / base;
    const float heightset = WINDOW_HEIGHT / base;
    perspectiveMat = glm::perspective(glm::radians(75.0f), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 1000.0f);
    orthoMat = glm::ortho(-1.0f * widthset, 1.0f * widthset, -1.0f * heightset, 1.0f * heightset, 0.0f, UI_CAM_Z - UI_Z);
    orthoCam.setEyeVec(glm::vec3(UI_CAM_X, UI_CAM_Y, UI_CAM_Z));
    orthoCam.setAtVec(glm::vec3(UI_CAM_X, UI_CAM_Y, UI_Z));
    orthoCam.setUpVec(glm::vec3(0.0f, 1.0f, 0.0f));
}

GamePlay::~GamePlay () {
    // delete planetaryB;
    // delete planetaryA;
    delete itemManager;
    delete enemyBulletManager;
    delete playerBulletManager;
    delete enemy;
    delete player;
    delete perspectiveSceneRoot;
    // delete hud;
}

void GamePlay::start () {
    // hud->init(PLAYER_LIVES);
    // planetaryA->init(PLANETARY_A_POS, PLANETARY_A_MAX_SIZE);
    // planetaryB->init(PLANETARY_B_POS, PLANETARY_B_MAX_SIZE);
    player->init(PLAYER_INIT_POS, 180.0f, glm::vec3(0.0f, 1.0f, 0.0f), PLAYER_COLOR, PLAYER_MAX_SIZE, AircraftSpeed::FAST, PLAYER_LIVES);
    enemy->init(ENEMY_INIT_POS, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), ENEMY_COLOR, ENEMY_MAX_SIZE, AircraftSpeed::NORMAL, 1);
    enemyAi.start(enemy, enemyBulletManager, ENEMY_BULLET_MAX_SIZE, ENEMY_BULLET_COLOR, BulletSpeed::NORMAL);
}

void GamePlay::renderPerspectiveScene () {
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    perspectiveSceneRoot->display(perspectiveMat, perspectiveCam.getMat(), glm::mat4(1.0f));
}

void GamePlay::renderOrthoScene () {
    // glClear(GL_DEPTH_BUFFER_BIT);
    // glDepthMask(GL_FALSE);
    // glDisable(GL_DEPTH_TEST);
    // hud->display(orthoMat, orthoCam.getMat(), glm::mat4(1.0f));
}

void GamePlay::update (const bool* asyncKeyBuf, std::queue<unsigned char>& discreteKeyBuf) {
    // Keyboard input handling
    handleAsyncKeyInput(asyncKeyBuf);
    handleDiscreteKeyInput(discreteKeyBuf);

    // Update objects
    perspectiveSceneRoot->update();

    // Collision handling
    if (gameMode == GAMEMODE_NONE) {
        handleHitNormal(playerBulletManager, enemy);
        handleHitNormal(enemyBulletManager, player);
    }
    else if (gameMode == GAMEMODE_ALL_PASS) {
        handleHitInstantKill(playerBulletManager, enemy);
        handleHitDodge(enemyBulletManager, player);
    }
    else if (gameMode == GAMEMODE_ALL_FAIL) {
        handleHitInstantKill(enemyBulletManager, player);
    }
    handleGotItem(player);
    
    // Update gameplay
    if (stage > MAX_STAGE)
        win();
    if (!enemy->isAlive() &&
        (glutGet(GLUT_ELAPSED_TIME) - enemy->getLastDeactivatedTime() >= ENEMY_REGEN_INTERVAL_SECE * 1000)) {
        enemy->init(ENEMY_INIT_POS, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), ENEMY_COLOR, ENEMY_MAX_SIZE, AircraftSpeed::NORMAL, stage);
        for (int i = 1 ; i < enemy->getLives() ; i ++)
            enemy->addShotgunBullet();
        enemyAi.start(enemy, enemyBulletManager, ENEMY_BULLET_MAX_SIZE, ENEMY_BULLET_COLOR, BulletSpeed::NORMAL);
    }
    // hud->setValue(stage, viewMode, renderingMode, gameMode, player->getLives());

    // Update view
    switch (viewMode) {
        case VIEWMODE_TPS:
            setViewTPS();
            break;
        case VIEWMODE_FPS:
            setViewFPS();
            break;
        case VIEWMODE_2D:
            setView2D();
            break;
    }
}

void GamePlay::handleAsyncKeyInput (const bool* asyncKeyBuf) {
    const bool* buf = asyncKeyBuf;
    if (buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
        player->move(PLAYER_FRAME::LEFT);
    else if (!buf[GLUT_KEY_LEFT] && buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
        player->move(PLAYER_FRAME::FRONT);
    else if (!buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
        player->move(-PLAYER_FRAME::LEFT);
    else if (!buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && buf[GLUT_KEY_DOWN])
        player->move(-PLAYER_FRAME::FRONT);
    else if (buf[GLUT_KEY_LEFT] && buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
        player->move(PLAYER_FRAME::LEFT + PLAYER_FRAME::FRONT);
    else if (!buf[GLUT_KEY_LEFT] && buf[GLUT_KEY_UP] && buf[GLUT_KEY_RIGHT] && !buf[GLUT_KEY_DOWN])
        player->move(PLAYER_FRAME::FRONT - PLAYER_FRAME::LEFT);
    else if (!buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && buf[GLUT_KEY_RIGHT] && buf[GLUT_KEY_DOWN])
        player->move(-PLAYER_FRAME::LEFT - PLAYER_FRAME::FRONT);
    else if (buf[GLUT_KEY_LEFT] && !buf[GLUT_KEY_UP] && !buf[GLUT_KEY_RIGHT] && buf[GLUT_KEY_DOWN])
        player->move(PLAYER_FRAME::LEFT - PLAYER_FRAME::FRONT);
}

void GamePlay::handleDiscreteKeyInput (std::queue<unsigned char>& discreteKeyBuf) {
    while (!discreteKeyBuf.empty()) {
        unsigned char key = discreteKeyBuf.front();
        discreteKeyBuf.pop();
        switch (key) {
            case ' ':
                if (gameMode != GAMEMODE_ALL_FAIL)
                    player->fire(playerBulletManager, PLAYER_BULLET_MAX_SIZE, PLAYER_BULLET_COLOR, BulletSpeed::FAST);
                break;
            case 'c':
                if (gameMode != GAMEMODE_ALL_PASS) {
                    gameMode = GAMEMODE_ALL_PASS;
                }
                else {
                    gameMode = GAMEMODE_NONE;
                }
                break;
            case 'f':
                if (gameMode != GAMEMODE_ALL_FAIL) {
                    gameMode = GAMEMODE_ALL_FAIL;
                }
                else {
                    gameMode = GAMEMODE_NONE;
                }
                break;
            case 'r':
                if (!renderingMode) {
                    renderingMode = true;
                    perspectiveSceneRoot->setWireframe(true);
                    // hud->setWireframe(true);
                }
                else {
                    renderingMode = false;
                    perspectiveSceneRoot->setWireframe(false);
                    // hud->setWireframe(false);
                }
                break;
            case 'v':
                if (viewMode == VIEWMODE_2D) {
                    viewMode = VIEWMODE_TPS;
                }
                else if (viewMode == VIEWMODE_TPS) {
                    viewMode = VIEWMODE_FPS;
                }
                else {
                    viewMode = VIEWMODE_2D;
                }
                break;
        }
    }
}

void GamePlay::setViewTPS () {
    const glm::vec3 playerPos = player->getWorldPos();
    const glm::vec3 playerFrontVec = player->getFrontVec();
    const glm::vec3 playerUpVec = player->getUpVec();
    const glm::vec3 camPos = glm::vec3(playerPos + (-playerFrontVec * 7.0f + playerUpVec * 3.5f));
    const glm::vec3 at = playerPos + playerFrontVec * glm::vec3(AXIS_LIMIT_ABS);
    const glm::vec3 camUp = glm::vec3(playerUpVec);
    perspectiveCam.set(camPos, at, camUp);
    player->setDraw(true);
}

void GamePlay::setViewFPS () {
    glm::vec3 playerPos = player->getWorldPos();
    const glm::vec3 camPos = playerPos;
    const glm::vec3 at = playerPos + player->getFrontVec() * glm::vec3(AXIS_LIMIT_ABS);
    const glm::vec3 camUp = player->getUpVec();
    perspectiveCam.set(camPos, at, camUp);
    player->setDraw(false);
}

void GamePlay::setView2D () {
    const glm::vec3 camPos = glm::vec3(0.0f, WORLD_LIMIT_ABS * 2.0f, 0.0f);
    const glm::vec3 at = glm::vec3(0.0f, 0.0f, 0.0f);
    const glm::vec3 camUp = glm::vec3(0.0f, 0.0f, -1.0f);
    perspectiveCam.set(camPos, at, camUp);
    player->setDraw(true);
}

void GamePlay::handleHitNormal (StraightMovingObjectManager* attackerBulletManager, Aircraft* target) {
    if (!target->isAlive())
        return;
    if (attackerBulletManager->deactivateObjectWhichIsIn(target)) {
        if (target == player)
            afterPlayerHit();
        else
            afterEnemyHit();
    }
}

void GamePlay::handleHitInstantKill (StraightMovingObjectManager* attackerBulletManager, Aircraft* target) {
    if (!target->isAlive())
        return;
    if (attackerBulletManager->deactivateObjectWhichIsIn(target)) {
        while (target->isAlive())
            target->loseLife();
        if (target == player)
            afterPlayerHit();
        else
            afterEnemyHit();
    }
}

void GamePlay::handleHitDodge (StraightMovingObjectManager* attackerBulletManager, Aircraft* target) {
    if (!target->isAlive())
        return;
    if (attackerBulletManager->deactivateObjectWhichIsIn(target)) { }
}

void GamePlay::handleGotItem (Aircraft* target) {
    if (!target->isAlive())
        return;
    if (itemManager->deactivateObjectWhichIsIn(target))
        target->addShotgunBullet();
}

void GamePlay::afterPlayerHit () {
    player->loseLife();
    if (!player->isAlive())
        lose();
    player->setRandomColor();
}

void GamePlay::afterEnemyHit () {
    enemy->loseLife();
    if (!enemy->isAlive()) {
        stage += 1;
        enemyAi.stop();
        itemManager->activateObject(enemy->getTranslate(), enemy->getAngleStack(), enemy->getRotateAxisStack(), ITEM_MAX_SIZE, ITEM_COLOR, BulletSpeed::SLOW);
    }
}

void GamePlay::win () {
    std::cout << "Win!" << std::endl;
    enemyAi.stop();
    glutDestroyWindow(glutGetWindow());
}

void GamePlay::lose () {
    std::cout << "Lose.." << std::endl;
    enemyAi.stop();
    glutDestroyWindow(glutGetWindow());
}