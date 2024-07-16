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

	// Create Fixture
	b2FixtureDef fixtureDef;
	fixtureDef.userData.pointer = (uintptr_t)(_fixtureData);
	fixtureDef.shape = &b2shape;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 0.0f;

	// Attach Shape to Body
	_body->CreateFixture(&fixtureDef);

	b2PolygonShape bottomSensor;
	bottomSensor.SetAsBox(width / 2.0f / pixels_per_meter, 0.05f, b2Vec2(0.0f, height / 2.0f / pixels_per_meter - 0.05f), 0.0f);

	b2FixtureDef sensorFixtureDef;
	sensorFixtureDef.shape = &bottomSensor;
	sensorFixtureDef.isSensor = true;  // Marcamos este fixture como sensor
	sensorFixtureDef.userData.pointer = (uintptr_t)(_fixtureData);  // Asignamos datos de usuario si es necesario
	_body->CreateFixture(&sensorFixtureDef);

	_texture.loadFromFile("assets/SpriteSheetTimesTwo.png");
	_startTile = new sf::Sprite();
	_middleTile = new sf::Sprite();
	_endTile = new sf::Sprite();

	_startTile->setTexture(_texture);
	_middleTile->setTexture(_texture);
	_endTile->setTexture(_texture);

	_startTile->setTextureRect({48, 288, 32, 32});
	_middleTile->setTextureRect({ 82, 288, 32, 32 });
	_endTile->setTextureRect({ 116, 288, 32, 32 });

	_startTile->setOrigin(_startTile->getGlobalBounds().width / 2.0f, _startTile->getGlobalBounds().height / 2.0f);
	_middleTile->setOrigin(_middleTile->getGlobalBounds().width / 2.0f, _middleTile->getGlobalBounds().height / 2.0f);
	_endTile->setOrigin(_endTile->getGlobalBounds().width / 2.0f, _endTile->getGlobalBounds().height / 2.0f);
}

void DestroyableTerrain::update()
{
	if (_isStarting) {
		_fallTimer += 0.1f;

		if (_fallTimer >= 3) {
			_fallTimer = 0.0f;
			_isDestroyed = true;	
			return;
		}
	}
}

void DestroyableTerrain::render(sf::RenderWindow& window) {
	b2Vec2 position = _body->GetPosition();
	float bodyWidth = getWidth(_body);

	// Ajuste de la posición del startTile en el borde izquierdo del cuerpo
	_startTile->setPosition((position.x * pixels_per_meter) - (bodyWidth / 2.0f), position.y * pixels_per_meter);
	window.draw(*_startTile);

	// Calcular el número de sprites de medio
	float widthInPixels = bodyWidth;
	int numMiddleTiles = static_cast<int>((widthInPixels - 64) / 32); // Restando 64 para los sprites de inicio y fin

	// Dibujar los sprites de medio
	for (int i = 0; i < numMiddleTiles; ++i) {
		_middleTile->setPosition((position.x * pixels_per_meter) - (bodyWidth / 2.0f) + 32 + i * 32, position.y * pixels_per_meter);
		window.draw(*_middleTile);
	}

	// Ajuste de la posición del endTile en el borde derecho del cuerpo
	_endTile->setPosition((position.x * pixels_per_meter) + (bodyWidth / 2.0f) - 32, position.y * pixels_per_meter);
	window.draw(*_endTile);
}

float DestroyableTerrain::getWidth(b2Body* body) {
	const b2Fixture* fixture = body->GetFixtureList();
	if (fixture) {
		const b2PolygonShape* shape = dynamic_cast<const b2PolygonShape*>(fixture->GetShape());
		if (shape) {
			float minX = shape->m_vertices[0].x;
			float maxX = shape->m_vertices[0].x;
			for (int i = 1; i < shape->m_count; ++i) {
				if (shape->m_vertices[i].x < minX) {
					minX = shape->m_vertices[i].x;
				}
				if (shape->m_vertices[i].x > maxX) {
					maxX = shape->m_vertices[i].x;
				}
			}
			return (maxX - minX) * pixels_per_meter;
		}
	}
	return 0;
}

void DestroyableTerrain::onBeginContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData().pointer;

	if (_topFixture != self && data && data->type == FixtureDataType::Player) {
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
