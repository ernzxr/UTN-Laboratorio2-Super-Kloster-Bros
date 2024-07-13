#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "constants.h"
#include "GlobalContactListener.h"

class Enemy : public ContactListener
{
private:
	sf::Texture _texture;
	sf::Sprite* _sprite;
	b2Body* _body;

	float _width = 32.0f;
	float _height = 52.0f;

	b2Vec2 _velocity{ 0.0f , 0.0f };
	float _moveSpeed = 2.0f;

	float _stateTime = 0.0f;

	float _frame = 0.0f;

	FixtureData _fixtureData;

	bool _isHit = false;
	bool _isDead = false;
	float _deathTimer = 0.0f;
public:
	Enemy(b2World& world, b2Vec2 position);

	~Enemy();

	void update();

	void render(sf::RenderWindow& window);
	bool isDead();

	virtual void onBeginContact(b2Fixture* self, b2Fixture* other) override;
	virtual void onEndContact(b2Fixture* self, b2Fixture* other) override;

};

