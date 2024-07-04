#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Player.h"
#include "TiledMap.h"

class Scene {
private:
	b2World& _world;
	TiledMap* _tiledMap;
	Player* _player;
	Enemy* _enemy;
	Enemy* _enemy2;
	Enemy* _enemy3;

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
    sf::Vector2f getCameraPosition();
    void render(sf::RenderWindow& window, bool paused);
};