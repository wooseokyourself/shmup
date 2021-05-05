#include "Hud.hpp"

void Hud::display (const glm::mat4& projection, const glm::mat4& lookAt, const glm::mat4& prevMat) {
    drawText();
    for (Object* heart : heartPtrs)
        heart->display(projection, lookAt, prevMat);
}

void Hud::init (const int playerLives) {
    for (int i = 0 ; i < playerLives ; i ++) {
        Object* heart = new Object;
        heart->loadModel("assets/models/love.obj");
        heart->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        heart->setLongestSideTo(0.1f);
        heart->setTranslate(glm::vec3(UI_MIN_X + (i * UI_MAX_X * 0.12), UI_Y - (UI_Y_HALF_ABS * 0.9f), UI_Z));
        heart->setDraw(true);
        heartPtrs.push_back(heart);
    }
}

void Hud::setValue (const uint8_t stage, const int viewMode, bool renderingMode, const int gameMode, const int playerLives) {
    stageText = "Stage " + std::to_string(stage);
    switch (viewMode) {
        case VIEWMODE_TPS:
            viewModeText = "View Mode: TPS";
            break;
        case VIEWMODE_FPS:
            viewModeText = "View Mode: FPS";
            break;
        case VIEWMODE_2D:
            viewModeText = "View Mode: 2D";
            break;
    }
    if (renderingMode)
        renderingModeText = "Rendering Mode On";
    else
        renderingModeText = "Rendering Mode Off";
    switch (gameMode) {
        case GAMEMODE_NONE:
            gameModeText = "";
            break;
        case GAMEMODE_ALL_PASS:
            gameModeText = "All Pass On";
            break;
        case GAMEMODE_ALL_FAIL:
            gameModeText = "All Fail On";
            break;
    }
    while (heartPtrs.size() > playerLives) {
        delete heartPtrs.back();
        heartPtrs.pop_back();
    }
}

void Hud::drawText () {
    glPushMatrix();
    glTranslatef(UI_MIN_X, UI_Y + (UI_Y_HALF_ABS * 0.9f), UI_Z);
    glRasterPos2d(0.0f, 0.0f);
    for (int i = 0 ; i < stageText.size() ; i ++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, stageText[i]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(UI_MIN_X, UI_Y + (UI_Y_HALF_ABS * 0.8f), UI_Z);
    glRasterPos2d(0.0f, 0.0f);
    for (int i = 0 ; i < viewModeText.size() ; i ++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, viewModeText[i]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(UI_MIN_X, UI_Y + (UI_Y_HALF_ABS * 0.75f), UI_Z);
    glRasterPos2d(0.0f, 0.0f);
    for (int i = 0 ; i < renderingModeText.size() ; i ++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, renderingModeText[i]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(UI_MIN_X, UI_Y + (UI_Y_HALF_ABS * 0.7f), UI_Z);
    glRasterPos2d(0.0f, 0.0f);
    for (int i = 0 ; i < gameModeText.size() ; i ++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, gameModeText[i]);
    glPopMatrix();
}