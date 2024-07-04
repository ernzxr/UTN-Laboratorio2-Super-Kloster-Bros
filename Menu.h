#pragma once
#include <SFML/Graphics.hpp>

class Menu {
public:
    sf::Texture _nuevaPTexture;
    sf::Sprite _nuevaPSprite;
    sf::Texture _rankingTexture;
    sf::Sprite _rankingSprite;
    sf::Texture _salirTexture;
    sf::Sprite _salirSprite;

    Menu() {
        _nuevaPTexture.loadFromFile("assets/NEW_GAME.png");
        _nuevaPSprite.setTexture(_nuevaPTexture);

        _rankingTexture.loadFromFile("assets/RANKING.png");
        _rankingSprite.setTexture(_rankingTexture);

        _salirTexture.loadFromFile("assets/SALIR.png");
        _salirSprite.setTexture(_salirTexture);
    }

    void render(sf::RenderWindow& window, int _mainMenuSelection);
};