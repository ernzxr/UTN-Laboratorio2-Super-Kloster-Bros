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

	//ESTRUCTURA 2 DE EJEMPLO

	float _width2 = 32.0f;
	float _height2 = 100.0f;
	b2Vec2 position2 = b2Vec2(500.0f, 436.0f);

	// Define Body
	b2BodyDef bodyDef2;
	bodyDef2.position.Set((position2.x + _width2 / 2.0f) / pixels_per_meter, (position2.y + _height2 / 2.0f) / pixels_per_meter);
	bodyDef.type = b2_staticBody;

	// Create Body
	_structure2 = _world.CreateBody(&bodyDef2);

	// Create Shape
	b2PolygonShape b2shape2;
	b2shape2.SetAsBox(_width2 / 2.0f / pixels_per_meter, _height2 / 2.0f / pixels_per_meter);

	//NEW
	FixtureData* fixtureData2 = new FixtureData();
	fixtureData2->type = FixtureDataType::GroundTile;
	fixtureData2->mapX = position2.x;
	fixtureData2->mapY = position2.y;

	// Create Fixture
	b2FixtureDef fixtureDef2;
	fixtureDef2.userData.pointer = (uintptr_t)fixtureData2;

	fixtureDef2.shape = &b2shape2;
	fixtureDef2.density = 0.0f;
	fixtureDef2.friction = 0.0f;

	// Attach Shape to Body
	_structure2->CreateFixture(&fixtureDef2);

	_structureShape2 = new sf::RectangleShape(sf::Vector2f(_width2, _height2));
	_structureShape2->setFillColor(sf::Color::Red);
	_structureShape2->setOrigin(_structureShape2->getGlobalBounds().width / 2.0f, _structureShape2->getGlobalBounds().height / 2.0f);
	_structureShape2->setScale(1, 1);

	_structure2->GetUserData().pointer = reinterpret_cast<uintptr_t>(_structureShape2);

	/**/

	// ESTRUCTURA 3 DE EJEMPLO

	b2Vec2 position3 = b2Vec2(900.0f, 436.0f);

	// Define Body
	b2BodyDef bodyDef3;
	bodyDef3.position.Set((position3.x + _width2 / 2.0f) / pixels_per_meter, (position3.y + _height2 / 2.0f) / pixels_per_meter);
	bodyDef3.type = b2_staticBody;

	// Create Body
	_structure3 = _world.CreateBody(&bodyDef3);

	// Create Shape
	b2PolygonShape b2shape3;
	b2shape3.SetAsBox(_width2 / 2.0f / pixels_per_meter, _height2 / 2.0f / pixels_per_meter);

	//NEW
	FixtureData* fixtureData3 = new FixtureData();
	fixtureData3->type = FixtureDataType::GroundTile;
	fixtureData3->mapX = position3.x;
	fixtureData3->mapY = position3.y;

	// Create Fixture
	b2FixtureDef fixtureDef3;
	fixtureDef3.userData.pointer = (uintptr_t)fixtureData3;

	fixtureDef3.shape = &b2shape3;
	fixtureDef3.density = 0.0f;
	fixtureDef3.friction = 0.0f;

	// Attach Shape to Body
	_structure3->CreateFixture(&fixtureDef3);

	_structureShape3 = new sf::RectangleShape(sf::Vector2f(_width2, _height2));
	_structureShape3->setFillColor(sf::Color::Red);
	_structureShape3->setOrigin(_structureShape3->getGlobalBounds().width / 2.0f, _structureShape3->getGlobalBounds().height / 2.0f);
	_structureShape3->setScale(1, 1);

	_structure3->GetUserData().pointer = reinterpret_cast<uintptr_t>(_structureShape3);





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

	_structureShape2->setPosition(_structure2->GetPosition().x * pixels_per_meter, _structure2->GetPosition().y * pixels_per_meter);
	_structureShape2->setRotation(_structure2->GetAngle() * deg_per_rad);
	window.draw(*_structureShape2);

	_structureShape3->setPosition(_structure3->GetPosition().x * pixels_per_meter, _structure3->GetPosition().y * pixels_per_meter);
	_structureShape3->setRotation(_structure3->GetAngle() * deg_per_rad);
	window.draw(*_structureShape3);
	
}
