#include "Pause.h"

void Pause::render(sf::RenderWindow& window, int _pauseMenuSelection, sf::Vector2f cameraPosition) {
    if (_pauseMenuSelection == 0) {
        _continueSprite.setPosition(cameraPosition.x - 240.0f, 100.0f);
        window.draw(_continueSprite);
    }
    else if (_pauseMenuSelection == 1) {
        _exitSprite.setPosition(cameraPosition.x - 240.0f, 100.0f);
        window.draw(_exitSprite);
    }
}