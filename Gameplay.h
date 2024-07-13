#pragma once
#include "TiledMap.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemySpawn.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Structures.h"


class Gameplay
{
private:
	b2World& _world;
	TiledMap* _tiledMap;
	Player* _player;
	EnemySpawn* _enemySpawn;
	Structures* _structures;
public:
	Gameplay(b2World& world);

	~Gameplay();

	void update();

	void render(sf::RenderWindow& window);

	void gameOver();

	void gameWin();

	void generateMap();

	void spawnPlayer();

	void spawnEnemies();

	void spawnStructures();

	sf::Vector2f getCameraPosition();
};

