#include "Gameplay.h"

Gameplay::Gameplay(b2World& world) : _world(world)
{
	_tiledMap = new TiledMap(_world);
	_player = new Player(_world, { 234, 480 });
	_enemy = new Enemy(world, { 971, 511 });
	_enemy2 = new Enemy(world, { 4043, 352 });
	_enemy3 = new Enemy(world, { 4565, 351 });
	_enemy4 = new Enemy(world, { 6191, 287 });
	_enemy5 = new Enemy(world, { 6448, 287 });
	_enemy6 = new Enemy(world, { 6798, 287 });
}

void Gameplay::update()
{
	// Restart the game with T
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
		_player->reset();
	}

	_player->cmd();
	_player->update();
	
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

	// Draw the Enemy
	_enemy->render(window);
	_enemy2->render(window);
	_enemy3->render(window);
	_enemy4->render(window);
	_enemy5->render(window);
	_enemy6->render(window);
}

void Gameplay::restart()
{
	_player->reset();
}

sf::Vector2f Gameplay::getCameraPosition()
{
	return _player->getPosition();
}
