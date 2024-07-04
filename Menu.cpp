#pragma once
#include "Menu.h"

Menu::Menu()
{
    if (!_musicMenu.openFromFile("assets/sounds/MenuMusic.wav"))
        return; // error

    _musicMenu.play();
    _musicMenu.setVolume(25.0f);

    _nuevaPTexture.loadFromFile("assets/NEW_GAME.png");
    _nuevaPSprite.setTexture(_nuevaPTexture);

    _rankingTexture.loadFromFile("assets/RANKING.png");
    _rankingSprite.setTexture(_rankingTexture);

    _salirTexture.loadFromFile("assets/SALIR.png");
    _salirSprite.setTexture(_salirTexture);
}

void Menu::render(sf::RenderWindow& window, int _mainMenuSelection) {
    sf::View currentView = window.getView();
    sf::Vector2f centerPosition = currentView.getCenter();

    float spriteWidth = 600.0f; // Ancho fijo del sprite
    float spriteHeight = 800.0f; // Alto fijo del sprite

    _nuevaPSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
    _rankingSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
    _salirSprite.setPosition(centerPosition.x - 400.0f, 0.0f);

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