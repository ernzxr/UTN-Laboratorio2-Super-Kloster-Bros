#pragma once
#include <vector>
#include <box2d/box2d.h>
#include "Enemy.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

class EnemySpawn
{
private:
	b2World& _world;
	tmx::Map& _tiled;

	std::vector<Enemy*> _enemies;
public:
	EnemySpawn(b2World& world, tmx::Map& tiled);

	~EnemySpawn();

	void spawnEnemies();

	std::vector<Enemy*>& getEnemies();
};

