#pragma once
#include <box2d/box2d.h>

class Player;

class ContactListener {
public:
	virtual void onBeginContact(b2Fixture* other) = 0;
	virtual void onEndContact(b2Fixture* other) = 0;
};

enum class FixtureDataType {
	Player,
	GroundTile,
	SpikeTile,
};

struct FixtureData {
	FixtureDataType type;
	ContactListener* listener;

	union {
		Player* player;
		struct { int mapX, mapY; };
	};


};


class GlobalContactListener : public b2ContactListener
{
public:
	virtual void BeginContact(b2Contact* contact) override;
	virtual void EndContact(b2Contact* contact) override;
};