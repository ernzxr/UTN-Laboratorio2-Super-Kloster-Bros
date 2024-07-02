#include "Obstacle.h"

Obstacle::Obstacle(b2World& world, b2Vec2 position)
{
	// Define Body
	b2BodyDef bodyDef;
	bodyDef.position.Set((position.x + _width / 2.0f) / pixels_per_meter, (position.y + _height / 2.0f) / pixels_per_meter);
	bodyDef.type = b2_staticBody;

	// Create Body
	_body = world.CreateBody(&bodyDef);

	// Create Shape
	b2PolygonShape b2shape;
	b2shape.SetAsBox(_width / 2.0f / pixels_per_meter, _height / 2.0f / pixels_per_meter);

	//NEW
	FixtureData* fixtureData = new FixtureData();
	fixtureData->type = FixtureDataType::GroundTile;
	fixtureData->mapX = position.x;
	fixtureData->mapY = position.y;

	// Create Fixture
	b2FixtureDef fixtureDef;
	//NEW
	fixtureDef.userData.pointer = (uintptr_t)fixtureData;
	fixtureDef.shape = &b2shape;
	fixtureDef.density = 0.0f;

	// Attach Shape to Body
	_body->CreateFixture(&fixtureDef);

	// Create SFML Shape
	_texture.loadFromFile("white-floor.png");
	_sprite = new sf::Sprite();
	_sprite->setTexture(_texture);
	_sprite->setOrigin(_sprite->getGlobalBounds().width / 2.0f, _sprite->getGlobalBounds().height / 2.0f);

	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(_sprite);
}