#pragma once
#include "Scene.h"

Scene::Scene(b2World& world) : _world(world)  {
	_tiledMap = new TiledMap(_world);
	_player = new Player(_world, { 400, 500 });

	_bgTexture.loadFromFile("assets/bg.jpg");
	_bgSprite.setTexture(_bgTexture);

	_continueTexture.loadFromFile("assets/CONTINUE.jpg");
	_continueSprite.setTexture(_continueTexture);
	_continueSprite.setPosition(170.0f, 0.0f);

	_exitTexture.loadFromFile("assets/EXIT.jpg");
	_exitSprite.setTexture(_exitTexture);
	_exitSprite.setPosition(170.0f, 0.0f);
}

void Scene::update() {
	_player->cmd();
	_player->update();
	_world.SetContactListener(new GlobalContactListener());
}

sf::Vector2f Scene::getCameraPosition() {
	return _player->getPosition();
}

void Scene::render(sf::RenderWindow& window, bool _paused, int _pauseMenuSelection) {
	window.clear();

	if (!_paused) {
		_world.Step(1.0f / 60, int32(10), int32(8));

		// Adjust the view to follow the player
		sf::View view = window.getView();
		sf::Vector2f playerPos = getCameraPosition();
		view.setCenter({ playerPos.x + 150,300 });
		window.setView(view);

		// Draw the background
		_bgSprite.setPosition(0, 0);
		window.draw(_bgSprite);

		// Draw the Player
		_player->render(window);

		// Draw the Map
		_tiledMap->render(window);
	}
	else {
		if (_pauseMenuSelection == 0) {
			window.draw(_continueSprite);
		}
		else if (_pauseMenuSelection == 1) {
			window.draw(_exitSprite);
		}
	}

	window.display();
}


