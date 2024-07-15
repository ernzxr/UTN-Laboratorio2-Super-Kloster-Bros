#pragma once
#include <vector>
#include <box2d/box2d.h>
#include "Star.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

class Collectable
{
private:
	b2World& _world;
	tmx::Map& _tiled;

	std::vector<Star*> _stars;
public:
	Collectable(b2World& world, tmx::Map& tiled);

	~Collectable();

	void createCollectables();

	std::vector<Star*>& getCollectables();
};

