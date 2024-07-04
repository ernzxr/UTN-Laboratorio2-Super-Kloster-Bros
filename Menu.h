#pragma once
#include <SFML/Graphics.hpp>

class Menu {
private:
    sf::Texture _nuevaPTexture;
    sf::Sprite _nuevaPSprite;

    sf::Texture _rankingTexture;
    sf::Sprite _rankingSprite;

    sf::Texture _salirTexture;
    sf::Sprite _salirSprite;
public:
    Menu();

    void render(sf::RenderWindow& window, int _mainMenuSelection);
};