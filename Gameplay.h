#pragma once
#include "TiledMap.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemySpawn.h"
#include "DestroyableTerrain.h"
#include "DestroyableTerrainSpawn.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Structures.h"
#include "Collectable.h"

class Gameplay
{
private:
	b2World& _world;
	TiledMap* _tiledMap;

	Player* _player;
	EnemySpawn* _enemySpawn;
	Structures* _structures;
	Collectable* _collectables;
	DestroyableTerrainSpawn* _destroyableTerrainSpawn;

	int _totalPoints = 0;
	int _tries = 1;
	bool _gameFinished = false;

	sf::RectangleShape* _deathScreen;
	int _deathScreenOpacity = 0;
	bool _isPlayerDead = false;
public:
	Gameplay(b2World& world);

	~Gameplay();

	void update();

	void render(sf::RenderWindow& window);

	void respawn();

	void gameWin();

	void gameOver();

	void generateMap();

	void spawnPlayer();

	void spawnEnemies();

	void spawnCollectables();

	void spawnStructures();

	void spawnDestroyableTerrains();

	void playDeathScreen();

	bool isGameFinished() const;

	sf::Vector2f getCameraPosition();
};

