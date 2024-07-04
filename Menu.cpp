#pragma once
#include "Menu.h"

Menu::Menu()
{
    //_nuevaPTexture.loadFromFile("assets/NEW_GAME.png");
    _nuevaPTexture.loadFromFile("assets/CONTINUE.jpg");
    _nuevaPSprite.setTexture(_nuevaPTexture);

    //_rankingTexture.loadFromFile("assets/RANKING.png");
    _rankingTexture.loadFromFile("assets/EXIT.jpg");
    _rankingSprite.setTexture(_rankingTexture);

    //_salirTexture.loadFromFile("assets/SALIR.png");
    _salirTexture.loadFromFile("assets/EXIT.jpg");
    _salirSprite.setTexture(_salirTexture);
}

void Menu::render(sf::RenderWindow& window, int _mainMenuSelection) {
    sf::View currentView = window.getView();
    sf::Vector2f centerPosition = currentView.getCenter();

    float spriteWidth = 600.0f; // Ancho fijo del sprite
    float spriteHeight = 800.0f; // Alto fijo del sprite

    _nuevaPSprite.setPosition(centerPosition.x - spriteWidth / 2, centerPosition.y - spriteHeight / 2 + 200); 
    _rankingSprite.setPosition(centerPosition.x - spriteWidth / 2, centerPosition.y - spriteHeight / 2 + 200);
    _salirSprite.setPosition(centerPosition.x - spriteWidth / 2, centerPosition.y - spriteHeight / 2 + 200);

    if (_mainMenuSelection == 0) {
        window.draw(_nuevaPSprite);
    }
    else if (_mainMenuSelection == 1) {
        window.draw(_rankingSprite);
    }
    else if (_mainMenuSelection == 2) {
        window.draw(_salirSprite);
    }
}