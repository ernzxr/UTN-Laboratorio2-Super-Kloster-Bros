#pragma once
#include "Gameplay.h"
#include <iostream>

Gameplay::Gameplay(b2World& world) : _world(world)
{
	generateMap();
	spawnStructures();
	spawnPlayer();
	spawnEnemies();
	spawnDestroyableTerrains();
	spawnCollectables();
	_deathScreen = new sf::RectangleShape;

	_lifesTexture.loadFromFile("assets/lifes.png");
	_lifesSprite.setTexture(_lifesTexture);

	_font.loadFromFile("assets/SuperMario256.ttf");
	_pointsText.setFont(_font);
	_pointsText.setCharacterSize(24); // Tama�o en p�xeles, no puntos.
	_pointsText.setFillColor(sf::Color::White);
	_pointsText.setOutlineThickness(2);
	_pointsText.setOutlineColor(sf::Color::Black);
	_deathScreen->setFillColor(sf::Color(0, 0, 0, 0));
}

Gameplay::~Gameplay()
{
	delete _tiledMap;
	delete _structures;
	delete _player;
	delete _enemySpawn;
	delete _destroyableTerrainSpawn;
	delete _collectables;
	delete _deathScreen;
}

void Gameplay::update()
{
	if (_isFrozen) {
		if (_deathScreenOpacity < 255) {
			_deathScreenOpacity += 15;  // Incrementa la opacidad gradualmente
		}
		_deathScreen->setFillColor(sf::Color(0, 0, 0, _deathScreenOpacity));

		// Asegura que la pantalla de muerte est� centrada en la posici�n del jugador
		sf::Vector2f playerPos = getCameraPosition();
		playerPos.x -= _deathScreen->getSize().x / 2 - 150;
		playerPos.y -= _deathScreen->getSize().y / 2;
		_deathScreen->setPosition(playerPos);


		if (_deathScreenOpacity >= 255) {
			respawn();
			_isFadingOut = true;
		}
		return;
	}

	if (_isFadingOut) {
		if (_deathScreenOpacity > 0) {
			_deathScreenOpacity -= 15;  // Decrementa la opacidad gradualmente
		}
		else {
			_isFadingOut = false;  // Termina el proceso de desvanecimiento
			_isPlayerDead = false;
		}
		_deathScreen->setFillColor(sf::Color(0, 0, 0, _deathScreenOpacity));

		sf::Vector2f playerPos = getCameraPosition();
		playerPos.x -= _deathScreen->getSize().x / 2 - 150;
		playerPos.y -= _deathScreen->getSize().y / 2;
		_deathScreen->setPosition(playerPos);
	}

	_world.Step(1.0f / 60, int32(10), int32(8));

	// Restart the game with T
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
		respawn();
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
	auto it = destroyableTerrains.begin();
	while (it != destroyableTerrains.end()) {
		(*it)->update();
		if ((*it)->isDestroyed()) {
			delete* it;
			it = destroyableTerrains.erase(it);  // Borra el elemento y avanza al siguiente v�lido.
		}
		else {
			++it;  // Avanza al siguiente elemento.
		}
	}
	
	// End the game if the player is dead or if the player wins
	auto& stars = _collectables->getCollectables();
	for (auto star : stars) {
		star->update();
		if (star->isCollected()) {
			if (star->isWinStar()) {
				_totalPoints += star->getPoints();
				stars.erase(std::remove(stars.begin(), stars.end(), star), stars.end());
				delete star;
				gameWin();
			}
			else {
				_totalPoints += star->getPoints();
				stars.erase(std::remove(stars.begin(), stars.end(), star), stars.end());
				delete star;
			}
		}
	}

	int lifesWidth = 177;
	int lifesHeight = 32;

	switch (_lifes) {
	case 5:
		_lifesSprite.setTextureRect({ 24, 22 + lifesHeight * 0, lifesWidth, lifesHeight });
		break;
	case 4:
		_lifesSprite.setTextureRect({ 24, 22 + lifesHeight * 1, lifesWidth, lifesHeight });
		break;
	case 3:
		_lifesSprite.setTextureRect({ 24, 22 + lifesHeight * 2, lifesWidth, lifesHeight });
		break;
	case 2:
		_lifesSprite.setTextureRect({ 24, 22 + lifesHeight * 3, lifesWidth, lifesHeight });
		break;
	case 1:
		_lifesSprite.setTextureRect({ 24, 22 + lifesHeight * 4, lifesWidth, lifesHeight });
		break;
	default:
		break;
	}

	_pointsText.setString(std::to_string(_totalPoints));

	if (_player->isDead()) {
		_isPlayerDead = true;
		_isFrozen = true;
	}
	// Respawn logic

	if (_isPlayerDead && !_isFadingOut) {
		_lifes--;
		if (_lifes < 1) {
			gameOver();
		}
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

	auto& stars = _collectables->getCollectables();
	for (auto star : stars) {
		star->render(window);
	}

	auto& destroyableTerrains = _destroyableTerrainSpawn->getDestroyableTerrains();
	for (auto& terrain : destroyableTerrains) {
		terrain->render(window);
	}

	// Ajustar la posici�n del sprite de las vidas para que siempre est� en la esquina superior izquierda de la vista
	sf::Vector2f viewCorner = window.mapPixelToCoords(sf::Vector2i(0, 0), view);
	_lifesSprite.setPosition(viewCorner.x + 15, viewCorner.y + 15);

	window.draw(_lifesSprite);

	// Ajusta la posici�n del texto del puntaje
	_pointsText.setPosition(viewCorner.x + 15, viewCorner.y + 50); // Ejemplo de posici�n

	window.draw(_pointsText);

	if (_isPlayerDead) {
		sf::Vector2u windowSize = window.getSize();
		_deathScreen->setSize(sf::Vector2f(windowSize.x + 200, windowSize.y + 4000));
		window.draw(*_deathScreen);
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

void Gameplay::spawnCollectables()
{
	_collectables = new Collectable(_world, _tiledMap->getMap());
}

void Gameplay::spawnStructures() {
	_structures = new Structures(_world, _tiledMap->getMap());
}

void Gameplay::spawnDestroyableTerrains() {
	_destroyableTerrainSpawn = new DestroyableTerrainSpawn(_world, _tiledMap->getMap());
}

bool Gameplay::isGameFinished() const
{
	return _gameFinished;
}

void Gameplay::respawn()
{
	_isFrozen = false;

	delete _destroyableTerrainSpawn;
	spawnDestroyableTerrains();
	
	delete _player;
	spawnPlayer();

	delete _enemySpawn;
	spawnEnemies();
}

void Gameplay::gameOver()
{
	_totalPoints += _lifes * 100;
	std::cout<<"Game Over!"<<std::endl;
	_gameFinished = true;
}

void Gameplay::gameWin()
{
	_totalPoints += _lifes * 100;
	std::cout<<"You win!"<<std::endl;
	_gameFinished = true;
}

sf::Vector2f Gameplay::getCameraPosition()
{
	return _player->getPosition();
}

