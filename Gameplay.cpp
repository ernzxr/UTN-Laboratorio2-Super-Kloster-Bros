#include "Gameplay.h"



Gameplay::Gameplay(b2World& world) : _world(world)
{
	_tiledMap = new TiledMap(_world);
	_player = new Player(_world, { 234, 480 });
	_enemy = new Enemy(world, { 960, 512 });
	_enemy2 = new Enemy(world, { 4032, 320 });
	_enemy3 = new Enemy(world, { 4544, 320 });
	_enemy4 = new Enemy(world, { 6176, 256 });
	_enemy5 = new Enemy(world, { 6432, 256 });
	_enemy6 = new Enemy(world, { 34, 480 });
	
}

void Gameplay::update()
{
	// Restart the game with T
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
		_player->reset();
	}

	_player->cmd();
	_player->update();

	auto& enemies = _tiledMap->getVector();
	for (auto enemy : enemies) {
		enemy->update();
	}
	
	// Update Enemy
	_enemy->update();
	_enemy2->update();
	_enemy3->update();
	_enemy4->update();
	_enemy5->update();
	_enemy6->update();
	

	_world.SetContactListener(new GlobalContactListener());
}

void Gameplay::render(sf::RenderWindow& window)
{
	_world.Step(1.0f / 60, int32(10), int32(8));

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

	auto& enemies = _tiledMap->getVector();
	for (auto enemy : enemies) {
		enemy->render(window);
	}

	// Draw the Enemy
	_enemy->render(window);
	_enemy2->render(window);
	_enemy3->render(window);
	_enemy4->render(window);
	_enemy5->render(window);
	_enemy6->render(window);
	
}

void Gameplay::gameOver()
{
}

sf::Vector2f Gameplay::getCameraPosition()
{
	return _player->getPosition();
}
