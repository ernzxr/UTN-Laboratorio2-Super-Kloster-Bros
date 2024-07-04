#include "Menu.h"

void Menu::render(sf::RenderWindow& window, int _mainMenuSelection) {
    window.clear();

    sf::Vector2f menuPos(window.getSize().x / 2, window.getSize().y / 2);
    if (_mainMenuSelection == 0) {
        _nuevaPSprite.setPosition(menuPos);
        window.draw(_nuevaPSprite);
    }
    else if (_mainMenuSelection == 1) {
        _rankingSprite.setPosition(menuPos);
        window.draw(_rankingSprite);
    }
    else if (_mainMenuSelection == 2) {
        _salirSprite.setPosition(menuPos);
        window.draw(_salirSprite);
    }

    window.display();
}