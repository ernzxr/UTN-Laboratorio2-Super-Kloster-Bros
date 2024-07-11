#pragma once
#include "TiledMap.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemySpawn.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Gameplay
{
private:
	b2World& _world;
	TiledMap* _tiledMap;
	Player* _player;
	EnemySpawn* _enemySpawn;
public:
	Gameplay(b2World& world);

	void update();

	void render(sf::RenderWindow& window);

	void gameOver();

	void gameWin();

	void generateMap();

	void spawnPlayer();

	void spawnEnemies();

	sf::Vector2f getCameraPosition();
};

