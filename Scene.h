#pragma once
#include <SFML/Graphics.hpp>
#include "TiledMap.h"
#include "Player.h"
#include "constants.h"
#include "Enemy.h"

class Scene
{
private:
	b2World& _world;
	TiledMap* _tiledMap;
	Player* _player;
	Enemy* _enemy;

	// Menu pausa
	sf::Texture _continueTexture;
	sf::Sprite _continueSprite;

	// Hacer que el pausa no cierre el juego si no que salga al menu principal.
	sf::Texture _exitTexture;
	sf::Sprite _exitSprite;

	// Menu principal
	// Hacer un menu principal con opciones de nueva partida, ranking, salir.
public:
	Scene(b2World& world);
	
	void update();

	void render(sf::RenderWindow& window, bool _paused, int _pauseMenuSelection);

	sf::Vector2f getCameraPosition();
};
