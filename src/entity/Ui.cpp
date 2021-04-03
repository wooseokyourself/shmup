#include "entity/Ui.hpp"

Ui::Ui (const int playerLives) {
    stageText = pushChild(TEXT);
    additionalText = pushChild(TEXT);
    for (int i = 0 ; i < playerLives ; i ++)
        heartPtrs.push_back(pushChild(new Heart));
}

Ui::~Ui () { }

void Ui::init () {
    stageText->setTranslate(WORLD_BOUND::LEFT + 0.05f, 0.9f, Window::MIN_DEPTH);
    stageText->setColor(1.0f, 1.0f, 1.0f, 0.5f);
    additionalText->setTranslate(WORLD_BOUND::LEFT + 0.05f, 0.8f, Window::MIN_DEPTH);
    additionalText->setColor(1.0f, 0.0f, 0.0f, 0.5f);
    for (int i = 0 ; i < heartPtrs.size() ; i ++) {
        TransformMatrix mat;
        mat.setTranslate(-0.9f + (i * 0.08), -0.9f, Window::MIN_DEPTH);
        ((Heart*)heartPtrs[i])->init(mat, 0.03f, Rgba(1.0f, 0.0f, 0.0f, 1.0f));
    }
}

void Ui::setValue (const uint8_t stage, const std::string additional, const int playerLives) {
    ((Text*)**stageText)->setText("Stage " + std::to_string(stage));
    ((Text*)**additionalText)->setText(additional);
    while (heartPtrs.size() > playerLives) {
        heartPtrs.pop_back();
        popBackChild();
    }
}

void Ui::update () {
    Object::update();
}

void Ui::display () const {
    Object::display();
}