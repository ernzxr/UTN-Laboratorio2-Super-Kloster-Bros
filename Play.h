#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Gameplay.h"

class Play
{
private:
	Gameplay* _gameplay;
public:
	Play(b2World& world);

	void update();

	void render(sf::RenderWindow& window);
};

