#pragma once
#include "GlobalContactListener.h"
#include "constants.h"
#include <box2d/box2d.h>
#include <vector>
#include <tmxlite/ObjectGroup.hpp>

class Terrain
{
private:
	b2Body* _body;

	FixtureData* _fixtureData;
public:
	Terrain(b2World& world, b2Vec2 position, float width, float height);

	Terrain(b2World& world, b2Vec2 position, std::vector<tmx::Vector2f> objectPoints, tmx::Object::Shape shape);

	~Terrain();
};

