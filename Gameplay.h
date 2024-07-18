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
#include "PlayerScore.h"
#include "ArchivoRank.h"

class Gameplay
{
private:
	b2World& _world;
	TiledMap* _tiledMap;

	ArchivoRank _archivoRank;

	sf::Sound _sound;
	sf::SoundBuffer _buffer;

	bool _firstDeath = true;
	bool _secondDeath = true;
	bool _thirdDeath = true;
	bool _fourthDeath = true;
	bool _ending = true;

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

	std::string _playerName = "";

	bool _tryAgain = false;
	bool _showCredits = false;

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

	bool getCredits() const;

	void setPlayerName(std::string playerName);

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

	sf::Vector2f getCameraPosition();
};

