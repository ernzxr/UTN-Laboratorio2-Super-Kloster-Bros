#pragma once
#include <vector>
#include <box2d/box2d.h>
#include "Obstacle.h"
#include "Terrain.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

class Structures
{
private:
	b2World& _world;
	tmx::Map& _tiled;

	std::vector<Obstacle*> _obstacles;
	std::vector<Terrain*> _terrains;
public:
	Structures(b2World& world, tmx::Map& tiled);

	~Structures();

	void spawnObstacles();

	void spawnTerrains();

	std::vector<Obstacle*>& getObstacles();

	std::vector<Terrain*>& getTerrains();
};

