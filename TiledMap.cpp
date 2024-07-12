#pragma once
#include "TiledMap.h"
#include <iostream>

TiledMap::TiledMap(b2World& world) : _world(world)
{
	if (_map.load("Tiled/Map.tmx"))
	{
		loadBackground();
	}
	else
	{
		std::cerr << "Failed to load map" << std::endl;
	}
}

void TiledMap::loadBackground() {
	const auto& layers = _map.getLayers();
	for (const auto& layer : layers)
	{
		if (layer->getType() == tmx::Layer::Type::Image)
		{
			const auto& imageLayer = layer->getLayerAs<tmx::ImageLayer>();

			if (!_bgTexture.loadFromFile("assets/bg.jpg"))
			{
				std::cerr << "Failed to load image layer" << std::endl;
				continue;
			}
			// Habilitar la repetición de la textura en el eje X (y Y si es necesario)
			_bgTexture.setRepeated(true);

			// Crear y configurar el sprite
			_bgSprite.setTexture(_bgTexture);
			// Ajustar el tamaño del sprite para que sea más grande que la textura si quieres que se repita
			// Aquí, como ejemplo, se establece el tamaño del sprite al doble de la textura original en X
			_bgSprite.setTextureRect(sf::IntRect(0, 0, _bgTexture.getSize().x * 5, _bgTexture.getSize().y));

			_bgSprite.setPosition(imageLayer.getOffset().x, imageLayer.getOffset().y);
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

b2Vec2 TiledMap::getPlayerSpawnPoint()
{
	const auto& layers = _map.getLayers();
	for (const auto& layer : layers)
	{
		if (layer->getType() == tmx::Layer::Type::Object)
		{
			const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
			const auto& objects = objectLayer.getObjects();
			for (const auto& object : objects)
			{
				tmx::Object::Shape shape = object.getShape();

				if (shape == tmx::Object::Shape::Point) {
					if (object.getName() == "Player") {
						tmx::Vector2f position = object.getPosition();
						return b2Vec2(position.x, position.y);
					}
				}
			}
		}
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

tmx::Map& TiledMap::getMap()
{
	return _map;
}
