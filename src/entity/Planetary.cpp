#include "entity/Planetary.hpp"

Planetary::Planetary () {
    star = pushChild(CIRCLE);
    orbit = star->pushChild(CIRCLE);
    satellite = orbit->pushChild(CIRCLE);
    
    starAngle = randomRealNumber(0.05f, 1.0f);
    orbitAngle = randomRealNumber(0.2f, 2.0f);
}

void Planetary::init (const TransformMatrix& mat, const GLfloat starRadius) {
    GLfloat orbitRadius = starRadius / 2.0f;
    GLfloat satelliteRadius = orbitRadius / 3.0f;
    
    setMatrix(mat);
    rotate(randomRealNumber(0.0f, 360.0f));
    ((Circle*)**star)->setRadius(starRadius);
    ((Circle*)**orbit)->setRadius(orbitRadius);
    ((Circle*)**satellite)->setRadius(satelliteRadius);

    orbit->setTranslate(0.0f, 3.0f * starRadius);
    satellite->setTranslate(2.0f * orbitRadius, 0.0f);

    star->setRandomColor();
    star->setColorAlpha(0.5f);
    orbit->setRandomColor();
    orbit->setColorAlpha(0.5f);
    satellite->setRandomColor();
    satellite->setColorAlpha(0.5f);
}

void Planetary::update () {
    star->rotate(starAngle);
    orbit->rotate(orbitAngle);
    Object::update();
}

void Planetary::diaplay () const {
    Object::display();
}