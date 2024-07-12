#pragma once
#include "EnemySpawn.h"

EnemySpawn::EnemySpawn(b2World& world, tmx::Map& tiled) : _world(world), _tiled(tiled)
{
	spawnEnemies();
}

EnemySpawn::~EnemySpawn()
{
	for (auto enemy : _enemies) {
		delete enemy;
	}
	_enemies.clear();
}

void EnemySpawn::spawnEnemies()
{

	// Returns a reference to the vector containing the layer data.
	const auto& layers = _tiled.getLayers();
	for (const auto& layer : layers)
	{
		if (layer->getType() == tmx::Layer::Type::Object)
		{
			const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
			const auto& objects = objectLayer.getObjects();
			for (const auto& object : objects)
			{
				tmx::Object::Shape shape = object.getShape();

				if (object.getName() == "Enemy") {
					if (shape == tmx::Object::Shape::Point) {
						tmx::Vector2f position = object.getPosition();
						_enemies.push_back(new Enemy(_world, b2Vec2(position.x, position.y + 12.0f)));
					}
				}
			}
		}
	}
}

std::vector<Enemy*>& EnemySpawn::getEnemies() {
	return _enemies;
}
