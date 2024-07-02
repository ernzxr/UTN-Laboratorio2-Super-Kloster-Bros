#pragma once
#include "TiledMap.h"


TiledMap::TiledMap(b2World& world) : _world(world)
{
	createFloor();
	createStructure();
}

void TiledMap::createStructure() {
	float _width = 300.0f;
	float _height = 32.0f;
	b2Vec2 position = b2Vec2(550.0f, 368.0f);

	// Define Body
	b2BodyDef bodyDef;
	bodyDef.position.Set((position.x + _width / 2.0f) / pixels_per_meter, (position.y + _height / 2.0f) / pixels_per_meter);
	bodyDef.type = b2_staticBody;

	// Create Body
	_structure = _world.CreateBody(&bodyDef);

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
	fixtureDef.userData.pointer = (uintptr_t)fixtureData;

	fixtureDef.shape = &b2shape;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 0.0f;

	// Attach Shape to Body
	_structure->CreateFixture(&fixtureDef);

	// Create SFML Shape
	_structureShape = new sf::RectangleShape(sf::Vector2f(_width, _height));
	_structureShape->setFillColor(sf::Color::Red);
	_structureShape->setOrigin(_structureShape->getGlobalBounds().width / 2.0f, _structureShape->getGlobalBounds().height / 2.0f);
	_structureShape->setScale(1, 1);

	_structure->GetUserData().pointer = reinterpret_cast<uintptr_t>(_structureShape);
}

void TiledMap::createFloor() {
	float _width = 1800.0f;
	float _height = 32.0f;
	b2Vec2 position = b2Vec2(0.0f, 568.0f);

	// Define Body
	b2BodyDef bodyDef;
	bodyDef.position.Set((position.x + _width / 2.0f) / pixels_per_meter, (position.y + _height / 2.0f) / pixels_per_meter);
	bodyDef.type = b2_staticBody;

	// Create Body
	_body = _world.CreateBody(&bodyDef);

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
	fixtureDef.userData.pointer = (uintptr_t)fixtureData;

	fixtureDef.shape = &b2shape;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 0.0f;

	// Attach Shape to Body
	_body->CreateFixture(&fixtureDef);

	// Create SFML Shape
	_shape = new sf::RectangleShape(sf::Vector2f(_width, _height));
	_shape->setFillColor(sf::Color::White);
	_shape->setOrigin(_shape->getGlobalBounds().width / 2.0f, _shape->getGlobalBounds().height / 2.0f);
	_shape->setScale(1, 1);

	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(_shape);
};

void TiledMap::render(sf::RenderWindow& window)
{
	// Temporal
	_shape->setPosition(_body->GetPosition().x * pixels_per_meter, _body->GetPosition().y * pixels_per_meter);
	_shape->setRotation(_body->GetAngle() * deg_per_rad);
	window.draw(*_shape);

	_structureShape->setPosition(_structure->GetPosition().x * pixels_per_meter, _structure->GetPosition().y * pixels_per_meter);
	_structureShape->setRotation(_structure->GetAngle() * deg_per_rad);
	window.draw(*_structureShape);
}
