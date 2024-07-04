#pragma once
#include <SFML/Graphics.hpp>

class Pause {
public:
    sf::Texture _continueTexture;
    sf::Sprite _continueSprite;
    sf::Texture _exitTexture;
    sf::Sprite _exitSprite;

    Pause() {
        _continueTexture.loadFromFile("assets/CONTINUE.jpg");
        _continueSprite.setTexture(_continueTexture);

        _exitTexture.loadFromFile("assets/EXIT.jpg");
        _exitSprite.setTexture(_exitTexture);
    }

    void render(sf::RenderWindow& window, int _pauseMenuSelection, sf::Vector2f cameraPosition);
};