#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "constants.h"
#include "GlobalContactListener.h"
#include <vector>
#include "Enemy.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/ImageLayer.hpp>
#include <tmxlite/LayerGroup.hpp>

class TiledMap
{
private:
    b2World& _world;

    tmx::Map _map;
    sf::Texture _tileset;

    sf::Texture _bgTexture;
    sf::Sprite _bgSprite;

    std::vector<Enemy*> _enemies;

public:
    TiledMap(b2World& world);

    void render(sf::RenderWindow& window);
    std::vector<Enemy*>& getVector();
};
