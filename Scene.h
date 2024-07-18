#pragma once
#include "constants.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Menu.h"
#include "Play.h"
#include "Pause.h"
#include "Rank.h"
#include "Credits.h"
#include "PlayerName.h"

class Scene {
private:
	Menu* _menu;
	Play* _play;
	Pause* _pause;
	TryAgain* _tryAgain;
	Rank* _ranking;
	Credits* _credits;
	PlayerName* _playerName;
	bool _music = true;
public:
	Scene(b2World& world);

	void update();

	void update(sf::Event event);

	void render(sf::RenderWindow& window);

	bool shouldExit() const;
};
