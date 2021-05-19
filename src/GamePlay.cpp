#include "GamePlay.hpp"

GamePlay::GamePlay() : viewMode(0) {
    stage = 1;
    gameMode = GAMEMODE_NONE;
    viewMode = VIEWMODE_TPS;
    renderingMode = true;

    perspectiveSceneRoot = new World(WORLD_GROUND_COLOR);
    player = new Aircraft;
    enemy = new Aircraft;
    playerBulletManager = new StraightMovingObjectManager(50);
    enemyBulletManager = new StraightMovingObjectManager(50);
    itemManager = new StraightMovingObjectManager(5);
    planetaryA = new Planetary("assets/models/sphere.obj", "assets/models/sphere.obj", "assets/models/sphere.obj");
    planetaryB = new Planetary("assets/models/sphere.obj", "assets/models/sphere.obj", "assets/models/sphere.obj");
    hud = new Hud(PLAYER_LIVES);
    
    perspectiveSceneRoot->loadShader(PHONG, "shader/phong_vertex.vert", "shader/phong_fragment.frag");
    player->loadShader(PHONG, "shader/phong_vertex.vert", "shader/phong_fragment.frag");
    enemy->loadShader(PHONG, "shader/phong_vertex.vert", "shader/phong_fragment.frag");
    playerBulletManager->loadShader(PHONG, "shader/phong_vertex.vert", "shader/phong_fragment.frag");
    enemyBulletManager->loadShader(PHONG, "shader/phong_vertex.vert", "shader/phong_fragment.frag");
    itemManager->loadShader(PHONG, "shader/phong_vertex.vert", "shader/phong_fragment.frag");
    planetaryA->loadShader(PHONG, "shader/phong_vertex.vert", "shader/phong_fragment.frag");
    planetaryB->loadShader(PHONG, "shader/phong_vertex.vert", "shader/phong_fragment.frag");
    hud->loadShader(NONLIGHT, "shader/nonlight_vertex.vert", "shader/nonlight_fragment.frag");

    player->loadModel("assets/models/player.obj");
    enemy->loadModel("assets/models/ebm314.obj");
    playerBulletManager->loadModel("assets/models/sphere.obj");
    enemyBulletManager->loadModel("assets/models/sphere.obj");
    itemManager->loadModel("assets/models/ammo_crate.obj");

    perspectiveSceneRoot->pushChild(planetaryA);
    perspectiveSceneRoot->pushChild(planetaryB);
    perspectiveSceneRoot->pushChild(player);
    perspectiveSceneRoot->pushChild(enemy);
    perspectiveSceneRoot->pushChild(playerBulletManager);
    perspectiveSceneRoot->pushChild(enemyBulletManager);
    perspectiveSceneRoot->pushChild(itemManager);
    
    camPos = glm::vec3(0.0f, 0.0f, 0.0f);
    camAt = glm::vec3(0.0f, 0.0f, 0.0f);
    camUp = glm::vec3(0.0f, 0.0f, 0.0f);
    const float base = WINDOW_HEIGHT < WINDOW_WIDTH ? WINDOW_HEIGHT : WINDOW_WIDTH;
    const float widthset = WINDOW_WIDTH / base;
    const float heightset = WINDOW_HEIGHT / base;
    perspectiveProjection = glm::perspective(glm::radians(75.0f), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 1000.0f);
    orthoProjection = glm::ortho(-1.0f * widthset, 1.0f * widthset, -1.0f * heightset, 1.0f * heightset, 0.0f, UI_CAM_Z - UI_Z);
    orthoLookAt = glm::lookAt(glm::vec3(UI_CAM_X, UI_CAM_Y, UI_CAM_Z), glm::vec3(UI_CAM_X, UI_CAM_Y, UI_Z), glm::vec3(0.0f, 1.0f, 0.0f));
}

GamePlay::~GamePlay() {
    delete planetaryB;
    delete planetaryA;
    delete itemManager;
    delete enemyBulletManager;
    delete playerBulletManager;
    delete enemy;
    delete player;
    delete perspectiveSceneRoot;
    delete hud;
}

void GamePlay::start() {
    planetaryA->init(PLANETARY_A_POS, PLANETARY_A_MAX_SIZE);
    planetaryB->init(PLANETARY_B_POS, PLANETARY_B_MAX_SIZE);
    player->setRandomColor();
    player->init(PLAYER_INIT_POS, 180.0f, glm::vec3(0.0f, 1.0f, 0.0f), PLAYER_MAX_SIZE, AircraftSpeed::FAST, PLAYER_LIVES);
    enemy->setRandomColor();
    enemy->init(ENEMY_INIT_POS, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), ENEMY_MAX_SIZE, AircraftSpeed::NORMAL, 1);
    playerBulletManager->init(glm::vec3(0.0f, 0.0f, 1.0f), PLAYER_BULLET_COLOR, BulletSpeed::FAST);
    enemyBulletManager->init(glm::vec3(0.0f, 0.0f, 1.0f), ENEMY_BULLET_COLOR, BulletSpeed::NORMAL);
    itemManager->init(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), BulletSpeed::NORMAL);
    enemyAi.start(enemy, enemyBulletManager, ENEMY_BULLET_MAX_SIZE);
}

void GamePlay::renderPerspectiveScene() {
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    if (renderingMode)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    perspectiveSceneRoot->display(perspectiveProjection * perspectiveLookAt, glm::mat4(1.0f), 
                                    glm::vec3(0.0f, 5.0f, 0.0f), camPos);
}

void GamePlay::renderOrthoScene() {
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    hud->display(orthoProjection * orthoLookAt);
}

void GamePlay::update(const bool* asyncKeyBuf, std::queue<unsigned char>& discreteKeyBuf) {
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
        enemy->init(ENEMY_INIT_POS, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), ENEMY_MAX_SIZE, AircraftSpeed::NORMAL, stage);
        for (int i = 1 ; i < enemy->getLives() ; i ++)
            enemy->addShotgunBullet();
        enemyAi.start(enemy, enemyBulletManager, ENEMY_BULLET_MAX_SIZE);
    }
    hud->setValue(stage, viewMode, renderingMode, gameMode, player->getLives());

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

void GamePlay::handleAsyncKeyInput(const bool* asyncKeyBuf) {
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

void GamePlay::handleDiscreteKeyInput(std::queue<unsigned char>& discreteKeyBuf) {
    while (!discreteKeyBuf.empty()) {
        unsigned char key = discreteKeyBuf.front();
        discreteKeyBuf.pop();
        switch (key) {
            case ' ':
                if (gameMode != GAMEMODE_ALL_FAIL)
                    player->fire(playerBulletManager, PLAYER_BULLET_MAX_SIZE);
                break;
            case 'c':
                if (gameMode != GAMEMODE_ALL_PASS)
                    gameMode = GAMEMODE_ALL_PASS;
                else 
                    gameMode = GAMEMODE_NONE;
                break;
            case 'f':
                if (gameMode != GAMEMODE_ALL_FAIL)
                    gameMode = GAMEMODE_ALL_FAIL;
                else
                    gameMode = GAMEMODE_NONE;
                break;
            case 'r':
                if (!renderingMode)
                    renderingMode = true;
                else
                    renderingMode = false;
                break;
            case 'v':
                if (viewMode == VIEWMODE_2D)
                    viewMode = VIEWMODE_TPS;
                else if (viewMode == VIEWMODE_TPS)
                    viewMode = VIEWMODE_FPS;
                else
                    viewMode = VIEWMODE_2D;
                break;
        }
    }
}

void GamePlay::setViewTPS() {
    const glm::vec3 playerPos = player->getWorldPos();
    const glm::vec3 playerFrontVec = player->getFrontVec();
    const glm::vec3 playerUpVec = player->getUpVec();
    camPos = glm::vec3(playerPos + (-playerFrontVec * 7.0f + playerUpVec * 3.5f));
    camAt = playerPos + playerFrontVec * glm::vec3(AXIS_LIMIT_ABS);
    camUp = glm::vec3(playerUpVec);
    perspectiveLookAt = glm::lookAt(camPos, camAt, camUp);
    player->setDraw(true);
    planetaryA->setDraw(true);
    planetaryB->setDraw(true);
}

void GamePlay::setViewFPS() {
    glm::vec3 playerPos = player->getWorldPos();
    camPos = playerPos;
    camAt = playerPos + player->getFrontVec() * glm::vec3(AXIS_LIMIT_ABS);
    camUp = player->getUpVec();
    perspectiveLookAt = glm::lookAt(camPos, camAt, camUp);
    player->setDraw(false);
    planetaryA->setDraw(true);
    planetaryB->setDraw(true);
}

void GamePlay::setView2D() {
    camPos = glm::vec3(0.0f, WORLD_LIMIT_ABS * 2.0f, 0.0f);
    camAt = glm::vec3(0.0f, 0.0f, 0.0f);
    camUp = glm::vec3(0.0f, 0.0f, -1.0f);
    perspectiveLookAt = glm::lookAt(camPos, camAt, camUp);
    player->setDraw(true);
    planetaryA->setDraw(false);
    planetaryB->setDraw(false);
}

void GamePlay::handleHitNormal(StraightMovingObjectManager* attackerBulletManager, Aircraft* target) {
    if (!target->isAlive())
        return;
    if (attackerBulletManager->deactivateObjectWhichIsIn(target)) {
        if (target == player)
            afterPlayerHit();
        else
            afterEnemyHit();
    }
}

void GamePlay::handleHitInstantKill(StraightMovingObjectManager* attackerBulletManager, Aircraft* target) {
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

void GamePlay::handleHitDodge(StraightMovingObjectManager* attackerBulletManager, Aircraft* target) {
    if (!target->isAlive())
        return;
    if (attackerBulletManager->deactivateObjectWhichIsIn(target)) { }
}

void GamePlay::handleGotItem(Aircraft* target) {
    if (!target->isAlive())
        return;
    if (itemManager->deactivateObjectWhichIsIn(target))
        target->addShotgunBullet();
}

void GamePlay::afterPlayerHit() {
    player->loseLife();
    if (!player->isAlive())
        lose();
    player->setRandomColor();
}

void GamePlay::afterEnemyHit() {
    enemy->loseLife();
    if (!enemy->isAlive()) {
        stage += 1;
        enemyAi.stop();
        itemManager->activateObject(enemy->cloneModelViewObj(), ITEM_MAX_SIZE);
        enemy->setRandomColor();
    }
}

void GamePlay::win() {
    std::cout << "Win!" << std::endl;
    enemyAi.stop();
    glutDestroyWindow(glutGetWindow());
}

void GamePlay::lose() {
    std::cout << "Lose.." << std::endl;
    enemyAi.stop();
    glutDestroyWindow(glutGetWindow());
}