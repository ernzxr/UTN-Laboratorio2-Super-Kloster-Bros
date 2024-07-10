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
	Enemy* _enemy;
	Enemy* _enemy2;
	Enemy* _enemy3;
	Enemy* _enemy4;
	Enemy* _enemy5;
	Enemy* _enemy6;

public:
	Gameplay(b2World& world);

	void update();

	void render(sf::RenderWindow& window);

	void gameOver();

	sf::Vector2f getCameraPosition();
};

