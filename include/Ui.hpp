#ifndef __UI__
#define __UI__

#include "core/Object.hpp"
#include "Constants.hpp"

class Ui : public Object {
public:
    virtual void draw () {
        /*
        glRasterPos2d(0.0f, 0.0f);
        for (int i = 0 ; i < stageText.size() ; i ++)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, stageText[i]);
        */
        for (Object* heart : heartPtrs)
            heart->draw();
    }
    void init (const int playerLives) {
        for (int i = 0 ; i < playerLives ; i ++) {
            Object* heart = new Object;
            heart->loadModel("assets/models/love.obj");
            heart->setColor(1.0f, 0.5, 0.5, 1.0f);
            heart->setLongestSideTo(0.05f);
            heart->setTranslate((UI_MIN_X * 0.9f) + (i * UI_MAX_X * 0.08), UI_MIN_Y, UI_MAX_Z * 0.9f);
        }
    }
    void setValue (const uint8_t stage, const std::string additional, const int playerLives) {
        stageText = "Stage " + std::to_string(stage);
        additionalText = additional;
        while (heartPtrs.size() > playerLives) {
            delete heartPtrs.back();
            heartPtrs.pop_back();
        }
    }

private:
    std::string stageText;
    std::string additionalText;
    std::vector<Object*> heartPtrs;
};

#endif