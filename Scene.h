#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Player.h"
#include "TiledMap.h"

class Scene {
private:
    b2World& _world;
    Player* _player;
    TiledMap* _tiledMap;
    sf::Texture _bgTexture;
    sf::Sprite _bgSprite;
public:
    Scene(b2World& world);
    void update();
    sf::Vector2f getCameraPosition();
    void render(sf::RenderWindow& window, bool paused);
};