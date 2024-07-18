#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Credits
{
private:
	sf::Texture _creditsTexture;
	sf::Sprite _creditsSprite;

	sf::Clock _clock;
	float _timeBetweenLines = 3.0f;
	size_t _currentLineIndex = 0;

	sf::Font _font;

	sf::Music _musicCredits;

	bool _selectedOption = false;
	bool _credits = false;

	std::vector<std::string> _vCredits = {
	   "SUPER KLOSTER BROS",
	   "LABORATORIO DE COMPUTACION II",
	   "UTN FACULTAD REGIONAL GENERAL PACHECO",
	   "ERNESTO JOSE RIVEIRO",
	   "FACUNDO CHENA GIL",
	   "LUCAS JAKOVCEVIC",
	   "DESARROLLADO EN 2024",
	   "GRACIAS POR JUGAR!"
	};
public:
	Credits();

	void update();

	void update(sf::Event event);

	void render(sf::RenderWindow& window);

	bool getCredits() const;

	bool creditsEnded() const;

	void open();

	void close();
};

