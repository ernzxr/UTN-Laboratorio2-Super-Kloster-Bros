#include "Gameplay.h"



Gameplay::Gameplay(b2World& world) : _world(world)
{
	generateMap();
	spawnPlayer();
	spawnEnemies();
}

void Gameplay::update()
{
	// Restart the game with T
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
		gameOver();
	}

	_player->cmd();
	_player->update();

	// Update Enemies
	auto& enemies = _enemySpawn->getEnemies();
	for (auto enemy : enemies) {
		enemy->update();
	}
	
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
	auto& enemies = _enemySpawn->getEnemies();
	for (auto enemy : enemies) {
		enemy->render(window);
	}
}

void Gameplay::spawnPlayer() {
	_player = new Player(_world, _tiledMap->getPlayerSpawnPoint());
}

void Gameplay::generateMap() {
	_tiledMap = new TiledMap(_world);
}

void Gameplay::spawnEnemies() {
	_enemySpawn = new EnemySpawn(_world, _tiledMap->getMap());
}

void Gameplay::gameOver()
{
	delete _player;
	spawnPlayer();

	delete _enemySpawn;
	spawnEnemies();
}

void Gameplay::gameWin()
{
}

sf::Vector2f Gameplay::getCameraPosition()
{
	return _player->getPosition();
}
