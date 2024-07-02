#pragma once
#include "Scene.h"

class Director
{
private:
	b2World& _world;
	Scene _scene;

	int _pauseMenuSelection;

	bool _paused;
	bool _exitRequested;
public:
	Director(b2World& world);

	void update();

	void render(sf::RenderWindow& window);

	void handleInput(sf::Event event);

	bool shouldExit();
};

