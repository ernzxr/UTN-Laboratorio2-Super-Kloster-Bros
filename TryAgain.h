#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class TryAgain
{
private:
    sf::SoundBuffer _buffer;
    sf::Sound _sound;

    sf::Texture _yesTexture;
    sf::Sprite _yesSprite;

    sf::Texture _noTexture;
    sf::Sprite _noSprite;

    int _tryAgainSelection = 0;
    int _selectedOption = -1;

    bool _tryAgain = false;
public:
    TryAgain();

	void update(sf::Event event);

	void render(sf::RenderWindow& window);

	int getSelectedOption() const;

    bool getTryAgain() const;

	void open();

	void close();
};

