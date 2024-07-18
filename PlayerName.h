#pragma once
#include <SFML/Graphics.hpp>

class PlayerName
{
private:
	sf::Texture _playerNameTexture;
	sf::Sprite _playerNameSprite;

	sf::Font _font;

	std::string _playerName = "";

	bool _setedPlayerName = false;
	bool _inPlayerName = false;
public:
	PlayerName();

	void update(sf::Event event);

	void render(sf::RenderWindow& window);

	std::string getPlayerName() const;

	bool getInPlayerName() const;

	bool setedPlayerName() const;

	void open();

	void close();
};

