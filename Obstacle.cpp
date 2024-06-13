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

	// Create Fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &b2shape;

	// Attach Shape to Body
	_body->CreateFixture(&fixtureDef);

	// Create SFML Shape
	_texture.loadFromFile("white-floor.png");
	_sprite = new sf::Sprite();
	_sprite->setTexture(_texture);
	_sprite->setOrigin(_texture.getSize().x / 2.0f, _texture.getSize().y / 2.0f);

	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(_sprite);
}