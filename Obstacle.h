#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "constants.h"
#include "GlobalContactListener.h"

class Obstacle
{
private:
    sf::Texture _texture;
    sf::Sprite* _sprite;
    b2Body* _body;

    float _width = 40.0f;
    float _height = 40.0f; 
public:
	Obstacle(b2World& world, b2Vec2 position);
};
