#include "entity/Ui.hpp"

Ui::Ui () {
    root->init(RECT);
    stageText = (Text*)**root->addChild(TEXT, FRONT);
    additionalText = (Text*)**root->addChild(TEXT, FRONT);
}

Ui::~Ui () { }
void Ui::init (const int playerLives) {
    Rect* windowBox = (Rect*)**root;
    windowBox->setSide(Window::WINDOW_HEIGHT, Window::WINDOW_WIDTH);
    windowBox->setTranslate(0.0f, 0.0f, Window::MAX_DEPTH);
    windowBox->setColor(0.0f, 0.0f, 0.0f, 0.0f);
    stageText->setTranslate(WORLD_BOUND::LEFT + 0.05f, 0.9f, Window::MIN_DEPTH);
    stageText->setColor(1.0f, 1.0f, 1.0f, 0.5f);
    additionalText->setTranslate(WORLD_BOUND::LEFT + 0.05f, 0.8f, Window::MIN_DEPTH);
    additionalText->setColor(1.0f, 0.0f, 0.0f, 0.5f);
    for (int i = 0 ; i < playerLives ; i ++) {
        lives.push_back(new Heart);
        ModelViewMat2D mat;
        mat.setTranslate(-0.9f + (i * 0.08), -0.9f, Window::MIN_DEPTH);
        lives.back()->init(mat, 0.03f, Rgba(1.0f, 0.0f, 0.0f, 1.0f));
    }
}

void Ui::update (const uint8_t stage, const std::string additionalText, const int playerLives) {
    stageText->setText("Stage " + std::to_string(stage));
    this->additionalText->setText(additionalText);
    while (lives.size() > playerLives)
        lives.pop_back();
}

void Ui::handlingWhenOutOfBound () { }

void Ui::display () const {
    root->display();
    for (Heart* heart : lives)
        heart->display();
}