#pragma once
#include "Gameplay.h"

Gameplay::Gameplay(b2World& world) : _world(world)
{
	generateMap();
	spawnStructures();
	spawnPlayer();
	spawnEnemies();
	spawnDestroyableTerrains();
}

Gameplay::~Gameplay()
{
	delete _tiledMap;
	delete _structures;
	delete _player;
	delete _enemySpawn;
	delete _destroyableTerrainSpawn;
}

void Gameplay::update()
{
	_world.Step(1.0f / 60, int32(10), int32(8));

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
		if (enemy->isDead()) {
			enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
			delete enemy;
		}
	}

	
	auto& destroyableTerrains = _destroyableTerrainSpawn->getDestroyableTerrains();
	for (auto& terrain : destroyableTerrains) {
		terrain->update();
		if (terrain->isDestroyed()) {
			destroyableTerrains.erase(std::remove(destroyableTerrains.begin(), destroyableTerrains.end(), terrain), destroyableTerrains.end());
			delete terrain;
		}
	}
	
	if (_player->isDead()) {
		gameOver();
	}
}

void Gameplay::render(sf::RenderWindow& window)
{
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

	auto& destroyableTerrains = _destroyableTerrainSpawn->getDestroyableTerrains();
	for (auto& terrain : destroyableTerrains) {
		terrain->render(window);
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

void Gameplay::spawnStructures() {
	_structures = new Structures(_world, _tiledMap->getMap());
}

void Gameplay::spawnDestroyableTerrains() {
	_destroyableTerrainSpawn = new DestroyableTerrainSpawn(_world, _tiledMap->getMap());
}

void Gameplay::gameOver()
{
	
	delete _destroyableTerrainSpawn;
	spawnDestroyableTerrains();
	
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
