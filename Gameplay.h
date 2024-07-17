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
#include "TryAgain.h"

class Gameplay
{
private:
	b2World& _world;
	TiledMap* _tiledMap;

	int _lifes = 5;
	sf::Texture _lifesTexture;
	sf::Sprite _lifesSprite;

	int _totalPoints = 0;
	sf::Font _font;
	sf::Text _pointsText;

	Player* _player;
	EnemySpawn* _enemySpawn;
	Structures* _structures;
	Collectable* _collectables;
	DestroyableTerrainSpawn* _destroyableTerrainSpawn;

	bool _gameFinished = false;
	bool _tryAgain = false;

	sf::RectangleShape* _deathScreen;
	int _deathScreenOpacity = 0;
	bool _isPlayerDead = false;
	bool _isFrozen = false;
	bool _isFadingOut = false;
public:
	Gameplay(b2World& world);

	~Gameplay();

	void update();

	void render(sf::RenderWindow& window);

	void respawn();

	bool getTryAgain() const;

	void tryAgain();

	void gameWin();

	void gameOver();

	void generateMap();

	void spawnPlayer();

	void spawnEnemies();

	void spawnCollectables();

	void spawnStructures();

	void spawnDestroyableTerrains();

	void spawnAll();

	bool isGameFinished() const;

	sf::Vector2f getCameraPosition();
};

