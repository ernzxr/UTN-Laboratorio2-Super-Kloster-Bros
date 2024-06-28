#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Player.h"
class Scene
{
private:
	b2World& _world;
	Player* _player;
	sf::Texture _bgTexture;
	sf::Sprite _bgSprite;
	void displayWorld(sf::RenderWindow& render);
public:
	Scene(b2World& world, Player* player);
	void update();
	void render(sf::RenderWindow& window);
	sf::Vector2f getCameraPosition();
};

