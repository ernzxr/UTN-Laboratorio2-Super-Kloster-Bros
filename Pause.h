#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Pause {
private:
    sf::SoundBuffer _buffer;
    sf::Sound _sound;

    sf::Texture _continueTexture;
    sf::Sprite _continueSprite;

    sf::Texture _exitTexture;
    sf::Sprite _exitSprite;

    int _pauseMenuSelection;
    int _selectedOption;

    bool _paused;
public:
    Pause();

    void update(sf::Event event);

    void render(sf::RenderWindow& window);

    bool getPaused() const;

    void open();

    void close();

    int getSelectedOption() const;
};