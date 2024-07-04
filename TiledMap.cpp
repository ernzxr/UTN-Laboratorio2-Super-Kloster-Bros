#pragma once
#include "TiledMap.h"
#include <iostream>

TiledMap::TiledMap(b2World& world) : _world(world)
{
	_bgTexture.loadFromFile("assets/bg.jpg");
	_bgSprite.setTexture(_bgTexture);
	_bgSprite.setPosition(0, 0);

	if (_map.load("Tiled/Map.tmx"))
	{
		// Returns a reference to the vector containing the layer data.
		const auto& layers = _map.getLayers();
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

					if (shape == tmx::Object::Shape::Rectangle)
					{
						tmx::Vector2f position = object.getPosition();
						float width = object.getAABB().width;
						float height = object.getAABB().height;

						// Define Body
						b2BodyDef bodyDef;
						bodyDef.position.Set((position.x + width / 2.0f) / pixels_per_meter, (position.y + height / 2.0f) / pixels_per_meter);
						bodyDef.type = b2_staticBody;

						// Create Body
						b2Body* body = world.CreateBody(&bodyDef);

						// Create Shape
						b2PolygonShape b2shape;
						b2shape.SetAsBox(width / 2.0f / pixels_per_meter, height / 2.0f / pixels_per_meter);

						// Type of Fixture Data
						FixtureData* fixtureData = new FixtureData();
						fixtureData->type = FixtureDataType::GroundTile;
						fixtureData->mapX = position.x;
						fixtureData->mapY = position.y;

						// Create Fixture
						b2FixtureDef fixtureDef;
						fixtureDef.userData.pointer = (uintptr_t)(fixtureData);
						fixtureDef.shape = &b2shape;
						fixtureDef.density = 0.0f;
						fixtureDef.friction = 0.0f;

						// Attach Shape to Body
						body->CreateFixture(&fixtureDef);
						
						// Debug
						//std::cout<< "Width: " << width << " Height: " << height << " Position: " << position.x << " " << position.y << std::endl;
						//std::cout << body->GetPosition().x << " ,"<< body->GetPosition().y << std::endl;
					}
				}
			}
		}

		// Returns a reference to the vector of tile sets used by the map.
		const auto& tilesets = _map.getTilesets();
		for (const auto& tileset : tilesets)
		{
			// Load textures based on tileset information.
			// This might involve loading the tileset image and creating textures for rendering.
			
			_tileset.loadFromFile("assets/tileset.png");
		}
	}
	else
	{
		std::cerr << "Failed to load map" << std::endl;
	}
}

void TiledMap::render(sf::RenderWindow& window)
{
	// Draw the background
	window.draw(_bgSprite);

	const int tileSize = 32;

	for (const auto& layer : _map.getLayers())
	{
		if (layer->getType() == tmx::Layer::Type::Tile)
		{
			// Use tileLayer data to render tiles or setup physics.
			const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
			const auto& tiles = tileLayer.getTiles();

			for (unsigned int y = 0; y < tileLayer.getSize().y; ++y)
			{
				for (unsigned int x = 0; x < tileLayer.getSize().x; ++x)
				{
					int tileID = tiles[y * tileLayer.getSize().x + x].ID;

					if (tileID == 0)
						continue;

					tileID--;

					sf::Vector2u textureSize = _tileset.getSize();
					int tu = tileID % (textureSize.x / tileSize);
					int tv = tileID / (textureSize.x / tileSize);

					sf::Sprite sprite;
					sprite.setTexture(_tileset);
					sprite.setTextureRect(sf::IntRect(tu * tileSize, tv * tileSize, tileSize, tileSize));
					sprite.setPosition(x * tileSize, y * tileSize);

					window.draw(sprite);
				}
			}
		}
	}
}