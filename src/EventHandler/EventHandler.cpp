#include "EventHandler/EventHandler.hpp"

void EventHandler::checkHit (Airplane* attacker, Airplane* target) {
    if (!target->isActivated())
        return;
    if (attacker->bulletManager.deactivateBulletIfItsIn(target->getLeftTop(), target->getRightBottom())) {
        std::cout << "Hit!" << std::endl;
        target->loseLife();
    }
}