#pragma once
#include "Scene.h"

Scene::Scene(b2World& world) : _world(world)  {
	_tiledMap = new TiledMap(_world);
	_player = new Player(_world, { 234, 480 });
	_enemy = new Enemy(_world, { 600, 480 });

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
	_enemy->update();

	_world.SetContactListener(new GlobalContactListener());
}

sf::Vector2f Scene::getCameraPosition() {
	return _player->getPosition();
}

void Scene::render(sf::RenderWindow& window, bool _paused, int _pauseMenuSelection) {
	window.clear();

	_world.Step(1.0f / 60, int32(10), int32(8));

	if (!_paused) {

		// Adjust the view to follow the player
		sf::View view = window.getView();
		sf::Vector2f playerPos = getCameraPosition();
		playerPos.x += 150; // La posicion del personaje + 150 para que se vea mas atras el personaje con respecto al centro.
		playerPos.y = (float(640) / 2); // El alto de la ventana dividido entre 2 para dejarlo fijo al medio.
		view.setCenter(playerPos);
		window.setView(view);

		// Draw the Map
		_tiledMap->render(window);

		// Draw the Player
		_player->render(window);

		//Draw the Enemy
		_enemy->render(window);

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


