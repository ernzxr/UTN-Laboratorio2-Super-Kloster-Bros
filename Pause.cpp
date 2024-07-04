#pragma
#include "Pause.h"

Pause::Pause()
{
    _continueTexture.loadFromFile("assets/CONTINUAR.png");
    _continueSprite.setTexture(_continueTexture);

    _exitTexture.loadFromFile("assets/PAUSA_SALIR.png");
    _exitSprite.setTexture(_exitTexture);
}

void Pause::render(sf::RenderWindow& window, int _pauseMenuSelection) {
    sf::View currentView = window.getView();
    sf::Vector2f centerPosition = currentView.getCenter();

    float spriteWidth = 600.0f; // Ancho fijo del sprite
    float spriteHeight = 800.0f; // Alto fijo del sprite
    
    _continueSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
    _exitSprite.setPosition(centerPosition.x - 400.0f, 0.0f);

    if (_pauseMenuSelection == 0) {
        //_continueSprite.setPosition(cameraPosition.x - 240.0f, 100.0f);
        window.draw(_continueSprite);
    }
    else if (_pauseMenuSelection == 1) {
        //_exitSprite.setPosition(cameraPosition.x - 240.0f, 100.0f);
        window.draw(_exitSprite);
    }
}

