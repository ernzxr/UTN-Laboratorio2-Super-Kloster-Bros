#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Gameplay.h"

class Play
{
private:
	Gameplay* _gameplay;

	bool _play;
	bool _pause;
public:
	Play(b2World& world);

	void update();

	void update(sf::Event event);

	void render(sf::RenderWindow& window);

	bool getPlay() const;

	bool getPause() const;

	void open();

	void close();
};

