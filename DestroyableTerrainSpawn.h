#pragma once
#include <vector>
#include <box2d/box2d.h>
#include "DestroyableTerrain.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

class DestroyableTerrainSpawn
{
private:
	b2World& _world;
	tmx::Map& _tiled;

	std::vector<DestroyableTerrain*> _destroyableTerrains;

public:
	DestroyableTerrainSpawn(b2World& world, tmx::Map& tiled);

	~DestroyableTerrainSpawn();

	void spawnDestroyableTerrains();

	std::vector<DestroyableTerrain*>& getDestroyableTerrains();
};

