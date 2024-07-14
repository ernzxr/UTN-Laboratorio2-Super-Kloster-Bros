#pragma once
#include "GlobalContactListener.h"
#include "constants.h"
#include <box2d/box2d.h>

class DestroyableTerrain : public ContactListener
{
private:
	b2Body* _body;
	
	FixtureData* _fixtureData;

	bool _isStarting = false;
	bool _isDestroyed = false;

	float _fallTimer = 0.0f;


public:
	DestroyableTerrain(b2World& world, b2Vec2 position, float width, float height);

	void update();
	bool isDestroyed();
	void resetGround(bool isDestroyed);
	virtual void onBeginContact(b2Fixture* self, b2Fixture* other) override;
	virtual void onEndContact(b2Fixture* self, b2Fixture* other) override;

	~DestroyableTerrain();
};

