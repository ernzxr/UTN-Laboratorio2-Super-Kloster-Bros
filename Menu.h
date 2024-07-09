#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Menu {
private:
    sf::Texture _nuevaPTexture;
    sf::Sprite _nuevaPSprite;

    sf::Texture _rankingTexture;
    sf::Sprite _rankingSprite;

    sf::Texture _salirTexture;
    sf::Sprite _salirSprite;

    sf::Music _musicMenu;

    int _mainMenuSelection;
    int _selectedOption;

    bool _inMainMenu;
public:
    Menu();

    void update(sf::Event event);

    void render(sf::RenderWindow& window);

    bool getMainMenu() const;

    bool getShouldExit() const;

    void open();

    void close();

    int getSelectedOption() const;
};