#include "Terrain.h"

Terrain::Terrain(b2World& world, b2Vec2 position, float width, float height)
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
	_fixtureData->type = FixtureDataType::GroundTile;

	// Create Fixture
	b2FixtureDef fixtureDef;
	fixtureDef.userData.pointer = (uintptr_t)(_fixtureData);
	fixtureDef.shape = &b2shape;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 0.0f;

	// Attach Shape to Body
	_body->CreateFixture(&fixtureDef);
}

Terrain::Terrain(b2World& world, b2Vec2 position, std::vector<tmx::Vector2f> objectPoints, tmx::Object::Shape shape)
{
	// Define Body
	b2BodyDef bodyDef;
	bodyDef.position.Set(position.x / pixels_per_meter, position.y / pixels_per_meter);
	bodyDef.type = b2_staticBody;

	// Create Body
	_body = world.CreateBody(&bodyDef);

	// Create Shape
	b2ChainShape chainShape;

	// Vertices
	std::vector<b2Vec2> points;
	if (shape == tmx::Object::Shape::Polyline)
	{
		for (auto& point : objectPoints)
		{
			points.push_back(b2Vec2(point.x / pixels_per_meter, point.y / pixels_per_meter));
		}

		// Ghost vertices
		b2Vec2 firstGhostVertex = points.front() - points[1];
		firstGhostVertex.Normalize();
		firstGhostVertex.x *= 0.1f;
		firstGhostVertex.y *= 0.1f;
		b2Vec2 prevVertex = points.front() + firstGhostVertex;

		b2Vec2 secondGhostVertex = points.back() - points[objectPoints.size() - 2];
		secondGhostVertex.Normalize();
		secondGhostVertex.x *= 0.1f;
		secondGhostVertex.y *= 0.1f;
		b2Vec2 nextVertex = points.back() + secondGhostVertex;

		chainShape.CreateChain(points.data(), points.size(), prevVertex, nextVertex);
	}
	else if (shape == tmx::Object::Shape::Polygon)
	{
		for (int i = 0; i < objectPoints.size() - 1; i++)
		{
			const auto& point = objectPoints[i];
			points.push_back(b2Vec2(point.x / pixels_per_meter, point.y / pixels_per_meter));
		}

		chainShape.CreateLoop(points.data(), points.size());

	}

	// Type of Fixture Data
	_fixtureData = new FixtureData();
	_fixtureData->type = FixtureDataType::GroundTile;

	// Create Fixture
	b2FixtureDef fixtureDef;
	fixtureDef.userData.pointer = (uintptr_t)(_fixtureData);
	fixtureDef.shape = &chainShape;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 0.0f;

	// Attach Shape to Body
	_body->CreateFixture(&fixtureDef);
}

Terrain::~Terrain()
{
	_body->GetWorld()->DestroyBody(_body);
}
