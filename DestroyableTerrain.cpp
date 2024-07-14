#include "DestroyableTerrain.h"
#include <iostream>

DestroyableTerrain::DestroyableTerrain(b2World& world, b2Vec2 position, float width, float height)
{
	// Define Body
	b2BodyDef bodyDef;
	bodyDef.position.Set((position.x + width / 2.0f) / pixels_per_meter, (position.y + height / 2.0f) / pixels_per_meter);
	bodyDef.type = b2_staticBody;

	// Create Body
	_body = world.CreateBody(&bodyDef);

	// Create Shape
	b2PolygonShape b2shape;
	b2shape.SetAsBox(width / 2.0f / pixels_per_meter, height / 2.0f / pixels_per_meter);

	// Type of Fixture Data
	_fixtureData = new FixtureData();
	_fixtureData->listener = this;
	_fixtureData->type = FixtureDataType::DestroyableTile;
	_fixtureData->mapX = position.x;
	_fixtureData->mapY = position.y;

	// Create Fixture
	b2FixtureDef fixtureDef;
	fixtureDef.userData.pointer = (uintptr_t)(_fixtureData);
	fixtureDef.shape = &b2shape;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 0.0f;

	// Attach Shape to Body
	_body->CreateFixture(&fixtureDef);
}

void DestroyableTerrain::update()
{
	if (_isStarting) {
		_fallTimer += 0.1f;

		if (_fallTimer >= 2) {
			_fallTimer = 0.0f;
			_isDestroyed = true;	
			return;
		}
	}
}

void DestroyableTerrain::onBeginContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData().pointer;

	if (data && data->type == FixtureDataType::Player) {
		//std::cout << "Player collided with DestroyableTerrain." << std::endl;
		_isStarting = true;
	}
}

void DestroyableTerrain::onEndContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData().pointer;

	if (data && data->type == FixtureDataType::Player) {
		_isStarting = false;
		_fallTimer += -0.1f;
	}
}


DestroyableTerrain::~DestroyableTerrain()
{
	_body->GetWorld()->DestroyBody(_body);
}

bool DestroyableTerrain::isDestroyed() {
	return _isDestroyed;
}

void DestroyableTerrain::resetGround(bool isDestroyed) {
	_isDestroyed = isDestroyed;
}
