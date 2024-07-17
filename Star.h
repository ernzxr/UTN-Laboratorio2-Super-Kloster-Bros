#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "constants.h"
#include "GlobalContactListener.h"

enum class StarType {
	Yellow = 0,
	Win,
};

class Star : public ContactListener
{
private:
	sf::Texture _texture;
	sf::Sprite* _sprite;

	b2Body* _body;

	FixtureData _fixtureData;

	float _width = 32.0f;
	float _height = 32.0f;

	int _points;

	StarType _starType;

	bool _isCollected = false;
	float _frame = 0.0f;
public:
	Star(b2World& world, b2Vec2 position, int points, StarType type = StarType::Yellow);
	
	~Star();

	void update();

	void render(sf::RenderWindow& window);

	int getPoints() const;

	bool isCollected() const;

	bool isWinStar() const;

	virtual void onBeginContact(b2Fixture* self, b2Fixture* other) override;

	virtual void onEndContact(b2Fixture* self, b2Fixture* other) override;
};

