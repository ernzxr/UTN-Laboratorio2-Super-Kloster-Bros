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
	sf::Texture _continueTexture;
	sf::Sprite _continueSprite;
	sf::Texture _exitTexture;
	sf::Sprite _exitSprite;
	int pauseMenuSelection;
	void displayWorld(sf::RenderWindow& render);
public:
	bool paused;
	bool exitRequested; // New flag for exit request
	Scene(b2World& world, Player* player);
	void update();
	void render(sf::RenderWindow& window);
	sf::Vector2f getCameraPosition();
	void handleInput(sf::Event event);
	bool shouldExit() const; // Method to check if exit is requested
};
