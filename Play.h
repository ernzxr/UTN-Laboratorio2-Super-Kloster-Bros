#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Gameplay.h"

class Play
{
private:
	b2World& _world;
	Gameplay* _gameplay = nullptr;

	sf::Music _musicMenu;

	bool _play = false;
	bool _pause = false;
public:
	Play(b2World& world);

	void update();

	void update(sf::Event event);

	void render(sf::RenderWindow& window);

	bool getPlay() const;

	bool getPause() const;

	void gameWin();

	void newGame();

	void tryAgain();

	void gameOver();
	
	bool getTryAgain();

	bool getCredits();

	void setPlayerName(std::string playerName);

	void createGameplay();

	void open();

	void close();
};

