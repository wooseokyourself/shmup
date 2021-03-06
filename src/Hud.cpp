#include "Hud.hpp"

using namespace std;

Hud::Hud(const int playerLives) {
    heart = new Object;
    viewModeTPS = new Object;
    viewModeFPS = new Object;
    viewMode2D = new Object;
    wireOn = new Object;
    wireOff = new Object;
    allPass = new Object;
    allFail = new Object;
    phongShading = new Object;
    gouraudShading = new Object;

    heart->loadModel("assets/models/love.obj");
    viewModeTPS->loadModel("assets/models/text3d_viewmode_tps.obj");
    viewModeFPS->loadModel("assets/models/text3d_viewmode_fps.obj");
    viewMode2D->loadModel("assets/models/text3d_viewmode_2d.obj");
    wireOn->loadModel("assets/models/text3d_wire_on.obj");
    wireOff->loadModel("assets/models/text3d_wire_off.obj");
    allPass->loadModel("assets/models/text3d_all_pass.obj");
    allFail->loadModel("assets/models/text3d_all_fail.obj");
    phongShading->loadModel("assets/models/text3d_phong_shading.obj");
    gouraudShading->loadModel("assets/models/text3d_gouraud_shading.obj");

    heart->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    viewModeTPS->setColor(glm::vec4(0.972f, 0.666f, 0.972f, 1.0f));
    viewModeFPS->setColor(glm::vec4(0.972f, 0.666f, 0.972f, 1.0f));
    viewMode2D->setColor(glm::vec4(0.972f, 0.666f, 0.972f, 1.0f));
    wireOn->setColor(glm::vec4(0.478f, 0.482f, 0.960f, 1.0f));
    wireOff->setColor(glm::vec4(0.478f, 0.482f, 0.960f, 1.0f));
    allPass->setColor(glm::vec4(0.478f, 0.960f, 0.6f, 1.0f));
    allFail->setColor(glm::vec4(0.478f, 0.960f, 0.6f, 1.0f));
    phongShading->setColor(glm::vec4(0.172f, 0.709f, 0.795f, 1.0f));
    gouraudShading->setColor(glm::vec4(0.172f, 0.709f, 0.795f, 1.0f));

    heart->setLongestSideTo(0.1f);
    viewModeTPS->setLongestSideTo(0.5f);
    viewModeFPS->setLongestSideTo(0.5f);
    viewMode2D->setLongestSideTo(0.5f);
    wireOn->setLongestSideTo(0.5f);
    wireOff->setLongestSideTo(0.5f);
    allPass->setLongestSideTo(0.5f);
    allFail->setLongestSideTo(0.5f);
    phongShading->setLongestSideTo(0.5f);
    gouraudShading->setLongestSideTo(0.5f);

    for (int i = 0; i < playerLives; i++) {
        ModelViewMat mat;
        mat.setTranslate(glm::vec3(UI_MIN_X + (i * UI_MAX_X * 0.12), UI_Y - (UI_Y_HALF_ABS * 0.9f), UI_Z));
        heartMats.push_back(mat);
    }

    glm::vec3 viewModePos(UI_MIN_X, UI_Y + (UI_Y_HALF_ABS * 0.8f), UI_Z);
    glm::vec3 renderingModePos(UI_MIN_X, UI_Y + (UI_Y_HALF_ABS * 0.75f), UI_Z);
    glm::vec3 gameModePos(UI_MIN_X, UI_Y + (UI_Y_HALF_ABS * 0.65f), UI_Z);
    glm::vec3 shadingTypePos(UI_MIN_X, UI_Y + (UI_Y_HALF_ABS * 0.55f), UI_Z);
    viewModeTPS->setTranslate(viewModePos);
    viewModeFPS->setTranslate(viewModePos);
    viewMode2D->setTranslate(viewModePos);
    wireOn->setTranslate(renderingModePos);
    wireOff->setTranslate(renderingModePos);
    allPass->setTranslate(gameModePos);
    allFail->setTranslate(gameModePos);
    phongShading->setTranslate(shadingTypePos);
    gouraudShading->setTranslate(shadingTypePos);
    viewModeTPS->update();
    viewModeFPS->update();
    viewMode2D->update();
    wireOn->update();
    wireOff->update();
    allPass->update();
    allFail->update();
    phongShading->update();
    gouraudShading->update();

    pushChild(viewModeTPS);
    pushChild(viewModeFPS);
    pushChild(viewMode2D);
    pushChild(wireOn);
    pushChild(wireOff);
    pushChild(allPass);
    pushChild(allFail);
    pushChild(phongShading);
    pushChild(gouraudShading);

    heart->setDraw(true);
}

Hud::~Hud() {
    delete heart;
    delete viewModeTPS;
    delete viewModeFPS;
    delete viewMode2D;
    delete wireOn;
    delete wireOff;
    delete allPass;
    delete allFail;
    delete phongShading;
    delete gouraudShading;
}

void Hud::display(const int shadingType, const glm::mat4& viewProjectionMat, const glm::mat4& parentModelViewMat,
                  const DirectionalLightFactors* dFactors, const std::vector<PointLightFactors*>& pFactorsArr, const glm::vec3& viewPos) {
    for (ModelViewMat mat : heartMats) {
        // heart->setModelViewMat(mat);
        heart->setTranslate(mat.getTranslate());
        heart->setRotateStack(mat.getAngleStack(), mat.getRotateAxisStack());
        heart->update();
        heart->display(shadingType, viewProjectionMat, glm::mat4(1.0f), dFactors, pFactorsArr, viewPos);
    }
    Object::display(shadingType, viewProjectionMat, glm::mat4(1.0f), dFactors, pFactorsArr, viewPos);
}

void Hud::loadShader(unsigned int type, const std::string& vertPath, const std::string& fragPath) {
    Object::loadShader(type, vertPath, fragPath);
    heart->setShader(type, shader[type]);
    viewModeTPS->setShader(type, shader[type]);
    viewModeFPS->setShader(type, shader[type]);
    viewMode2D->setShader(type, shader[type]);
    wireOn->setShader(type, shader[type]);
    wireOff->setShader(type, shader[type]);
    allPass->setShader(type, shader[type]);
    allFail->setShader(type, shader[type]);
    phongShading->setShader(type, shader[type]);
    gouraudShading->setShader(type, shader[type]);
}

void Hud::setShader(unsigned int type, Shader* loadedShader) {
    Object::setShader(type, loadedShader);
    heart->setShader(type, shader[type]);
    viewModeTPS->setShader(type, shader[type]);
    viewModeFPS->setShader(type, shader[type]);
    viewMode2D->setShader(type, shader[type]);
    wireOn->setShader(type, shader[type]);
    wireOff->setShader(type, shader[type]);
    allPass->setShader(type, shader[type]);
    allFail->setShader(type, shader[type]);
    phongShading->setShader(type, shader[type]);
    gouraudShading->setShader(type, shader[type]);
}

void Hud::setValue(const uint8_t stage, const int viewMode, bool renderingMode, const int gameMode, const int shadingType, const int playerLives) {
    stageText = "Stage " + std::to_string(stage);
    switch (viewMode) {
        case VIEWMODE_TPS:
            viewModeTPS->setDraw(true);
            viewModeFPS->setDraw(false);
            viewMode2D->setDraw(false);
            break;
        case VIEWMODE_FPS:
            viewModeTPS->setDraw(false);
            viewModeFPS->setDraw(true);
            viewMode2D->setDraw(false);
            break;
        case VIEWMODE_2D:
            viewModeTPS->setDraw(false);
            viewModeFPS->setDraw(false);
            viewMode2D->setDraw(true);
            break;
    }
    if (renderingMode) {
        wireOn->setDraw(true);
        wireOff->setDraw(false);
    }
    else {
        wireOn->setDraw(false);
        wireOff->setDraw(true);
    }
    switch (gameMode) {
        case GAMEMODE_NONE:
            allPass->setDraw(false);
            allFail->setDraw(false);
            break;
        case GAMEMODE_ALL_PASS:
            allPass->setDraw(true);
            allFail->setDraw(false);
            break;
        case GAMEMODE_ALL_FAIL:
            allPass->setDraw(false);
            allFail->setDraw(true);
            break;
    }
    if (shadingType == PHONG) {
        phongShading->setDraw(true);
        gouraudShading->setDraw(false);
    }
    else {
        phongShading->setDraw(false);
        gouraudShading->setDraw(true);
    }
    while (heartMats.size() > playerLives)
        heartMats.pop_back();
}