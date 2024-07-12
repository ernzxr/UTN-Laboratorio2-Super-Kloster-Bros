#pragma once
#include "Structures.h"

Structures::Structures(b2World& world, tmx::Map& tiled) : _world(world), _tiled(tiled)
{
	spawnObstacles();
	spawnTerrains();
}

Structures::~Structures()
{
	for (auto terrain : _terrains) {
		delete terrain;
	}
	_terrains.clear();

	for (auto obstacle : _obstacles) {
		delete obstacle;
	}
	_obstacles.clear();
}

void Structures::spawnObstacles()
{
	const auto& layers = _tiled.getLayers();
	for (const auto& layer : layers)
	{
		if (layer->getType() == tmx::Layer::Type::Object)
		{
			const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
			const auto& objects = objectLayer.getObjects();
			for (const auto& object : objects)
			{
				// Access object properties, e.g., object.getName(), object.getPosition(), etc.
				// Use this information to spawn entities or configure the game world.
				tmx::Object::Shape shape = object.getShape();

				if (object.getName() == "Spike") {
					tmx::Vector2f position = object.getPosition();

					if (shape == tmx::Object::Shape::Rectangle)
					{
						float width = object.getAABB().width;
						float height = object.getAABB().height;

						_obstacles.push_back(new Obstacle(_world, b2Vec2(position.x, position.y), width, height));
					}
					else if (shape == tmx::Object::Shape::Polyline || shape == tmx::Object::Shape::Polygon) {
						_obstacles.push_back(new Obstacle(_world, b2Vec2(position.x, position.y), object.getPoints(), shape));
					}
				}
			}
		}
	}
}

void Structures::spawnTerrains()
{
	const auto& layers = _tiled.getLayers();
	for (const auto& layer : layers)
	{
		if (layer->getType() == tmx::Layer::Type::Object)
		{
			const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
			const auto& objects = objectLayer.getObjects();
			for (const auto& object : objects)
			{
				// Access object properties, e.g., object.getName(), object.getPosition(), etc.
				// Use this information to spawn entities or configure the game world.
				tmx::Object::Shape shape = object.getShape();

				if (object.getName() == "Terrain") {
					tmx::Vector2f position = object.getPosition();

					if (shape == tmx::Object::Shape::Rectangle)
					{
						float width = object.getAABB().width;
						float height = object.getAABB().height;

						_terrains.push_back(new Terrain(_world, b2Vec2(position.x, position.y), width, height));
					}
					else if (shape == tmx::Object::Shape::Polyline || shape == tmx::Object::Shape::Polygon) {
						_terrains.push_back(new Terrain(_world, b2Vec2(position.x, position.y), object.getPoints(), shape));
					}
				}
			}
		}
	}
}

std::vector<Obstacle*>& Structures::getObstacles()
{
	return _obstacles;
}

std::vector<Terrain*>& Structures::getTerrains()
{
	return _terrains;
}
