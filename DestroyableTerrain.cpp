#include "DestroyableTerrain.h"

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
	if (_isDestroyed) {
		_fallTimer += 0.1f;

		if (_fallTimer >= 2) {
			_body->SetTransform(b2Vec2(_body->GetPosition().x, 1000.0f / pixels_per_meter), _body->GetAngle());
			_fallTimer = 0.0f;
			_body->GetWorld()->DestroyBody(_body);
			_body = nullptr;
			return;
		}
	}

}

void DestroyableTerrain::onBeginContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData().pointer;

	if (data->type == FixtureDataType::Player) {
		_isDestroyed = true;
	}
}

void DestroyableTerrain::onEndContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData().pointer;
}

DestroyableTerrain::~DestroyableTerrain()
{
	_body->GetWorld()->DestroyBody(_body);
}
