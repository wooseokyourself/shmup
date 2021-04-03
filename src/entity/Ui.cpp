#include "entity/Ui.hpp"
#include <iostream>
using namespace std;

Ui::Ui (const int playerLives) {
    stageText = pushChild(TEXT, FRONT);
    additionalText = pushChild(TEXT, FRONT);
    
    for (int i = 0 ; i < playerLives ; i ++) {
        Heart* heart = new Heart;
        pushChild(heart);
        lives.push_back(heart);
    }
}

Ui::~Ui () { }

void Ui::init () {
    stageText->setTranslate(WORLD_BOUND::LEFT + 0.05f, 0.9f);
    stageText->setColor(1.0f, 1.0f, 1.0f, 0.5f);
    additionalText->setTranslate(WORLD_BOUND::LEFT + 0.05f, 0.8f);
    additionalText->setColor(1.0f, 0.0f, 0.0f, 0.5f);
    for (int i = 0 ; i < lives.size() ; i ++) {
        TransformMatrix mat;
        mat.setTranslate(-0.9f + (i * 0.08), -0.9f);
        lives[i]->init(mat, 0.03f, Rgba(1.0f, 0.0f, 0.0f, 1.0f));
    }
}

void Ui::setValue (const uint8_t stage, const std::string additional, const int playerLives) {
    ((Text*)**stageText)->setText("Stage " + std::to_string(stage));
    ((Text*)**additionalText)->setText(additional);
    while (lives.size() > playerLives) {
        lives.pop_back();
        popBackChild();
    }
}

void Ui::update () {
    Object::update();
}

void Ui::display () const {
    Object::display();
}