#include "Collectable.h"

Collectable::Collectable(b2World& world, tmx::Map& tiled) : _world(world), _tiled(tiled)
{
		createCollectables();
}

Collectable::~Collectable()
{
	for (auto star : _stars) {
		delete star;
	}
	_stars.clear();
}

void Collectable::createCollectables()
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

				if (object.getName() == "Star") {
					if (shape == tmx::Object::Shape::Point) {
						tmx::Vector2f position = object.getPosition();
						_stars.push_back(new Star(_world, b2Vec2(position.x, position.y), 100));
					}
				}
				if (object.getName() == "WinStar") {
					if (shape == tmx::Object::Shape::Point) {
						tmx::Vector2f position = object.getPosition();
						_stars.push_back(new Star(_world, b2Vec2(position.x, position.y), 1000, StarType::Win));
					}
				}
			}
		}
	}
}

std::vector<Star*>& Collectable::getCollectables()
{
	return _stars;
}
