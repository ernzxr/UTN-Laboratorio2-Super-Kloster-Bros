#include "DestroyableTerrainSpawn.h"

DestroyableTerrainSpawn::DestroyableTerrainSpawn(b2World& world, tmx::Map& tiled) : _world(world), _tiled(tiled)
{
	spawnDestroyableTerrains();
}

DestroyableTerrainSpawn::~DestroyableTerrainSpawn()
{
	for (auto destroyableTerrain : _destroyableTerrains) {
		delete destroyableTerrain;
	}
	_destroyableTerrains.clear();
}

void DestroyableTerrainSpawn::spawnDestroyableTerrains()
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

				if (object.getName() == "DestroyableTerrain") {
					
					tmx::Vector2f position = object.getPosition();
					float width = object.getAABB().width;
					float height = object.getAABB().height;

					_destroyableTerrains.push_back(new DestroyableTerrain(_world, b2Vec2(position.x, position.y), width, height));
				}
			}
		}
	}
}

std::vector<DestroyableTerrain*>& DestroyableTerrainSpawn::getDestroyableTerrains()
{
	return _destroyableTerrains;
}
