#pragma once
#include "TiledMap.h"
#include "Player.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Gameplay
{
private:
	b2World& _world;
	TiledMap* _tiledMap;
	Player* _player;

public:
	Gameplay(b2World& world);

	void update();

	void render(sf::RenderWindow& window);

	void gameOver();

	sf::Vector2f getCameraPosition();
};

