#pragma once
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ArchivoRank.h"

class Rank
{
private:
    sf::SoundBuffer _buffer;
    sf::Sound _sound;

    sf::Texture _topTexture;
    sf::Sprite _topSprite;

    sf::Texture _globalTexture;
    sf::Sprite _globalSprite;

    ArchivoRank _archivoRank;

    int _rankMenuSelection = 0;
    int _selectedOption = -1;

    bool _inRank = false;
public:
    Rank();

	void update(sf::Event event);

	void render(sf::RenderWindow& window);

	bool getRank() const;

	void open();

	void close();

	int getSelectedOption() const;
};

