#include "Scene.h"

Scene::Scene(b2World& world) : _world(world)  {
	_tiledMap = new TiledMap(_world);
	_player = new Player(_world, { 234, 511 });
	_enemy = new Enemy(_world, { 971, 511 });
	_enemy2 = new Enemy(_world, { 4043, 352 });
	_enemy3 = new Enemy(_world, { 4565, 351 });
	_enemy4 = new Enemy(_world, { 6191, 287 });
	_enemy5 = new Enemy(_world, { 6448, 287 });
	_enemy6 = new Enemy(_world, { 6798, 287 });


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
	_enemy2->update();
	_enemy3->update();
	_enemy4->update();
	_enemy5->update();
	_enemy6->update();

	_world.SetContactListener(new GlobalContactListener());
}

sf::Vector2f Scene::getCameraPosition() {
    return _player->getPosition();
}

void Scene::render(sf::RenderWindow& window, bool paused) {
    window.clear();

    if (!paused) {
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
		_enemy2->render(window);
		_enemy3->render(window);
		_enemy4->render(window);
		_enemy5->render(window);
		_enemy6->render(window);
		

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


        // Draw the background
        _bgSprite.setPosition(0, 0);

        window.draw(_bgSprite);
        _tiledMap->render(window);

        // Draw the Player
        _player->render(window);

        // Draw the Map
    }

    window.display();
}