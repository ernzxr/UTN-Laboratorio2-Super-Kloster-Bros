#pragma once
#include "constants.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Menu.h"
#include "Play.h"
#include "Pause.h"

class Scene {
private:
	Menu* _menu;
	Play* _play;
	Pause* _pause;
public:
	Scene(b2World& world);

	void update();

	void update(sf::Event event);

	void render(sf::RenderWindow& window);

	bool shouldExit() const;
};
