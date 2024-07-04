#pragma once
#include <SFML/Graphics.hpp>

class Pause {
private:
    sf::Texture _continueTexture;
    sf::Sprite _continueSprite;

    sf::Texture _exitTexture;
    sf::Sprite _exitSprite;
public:
    Pause();

    void render(sf::RenderWindow& window, int _pauseMenuSelection);
};