#include "Director.h"

Director::Director(b2World& world) {
	_scene = new Scene(world);
	_paused = false;
	_pauseMenuSelection = 0;
	_exitRequested = false;
	_menuClosed = false;
	_inMainMenu = true;
	_mainMenuSelection = 0;
}

void Director::update() {
	_scene->update(_paused, _pauseMenuSelection, _inMainMenu, _mainMenuSelection);
}

void Director::render(sf::RenderWindow& window) {
	_scene->render(window, _paused, _pauseMenuSelection, _inMainMenu, _mainMenuSelection);
}

void Director::handleInput(sf::Event event) {
	if (_inMainMenu) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Down) {
				_mainMenuSelection = (_mainMenuSelection + 1) % 3; // Alternates between 0, 1, and 2
			}
			else if (event.key.code == sf::Keyboard::Up) {
				_mainMenuSelection = (_mainMenuSelection + 2) % 3; // Alternates between 0, 1, and 2
			}
			else if (event.key.code == sf::Keyboard::Enter) {
				if (_mainMenuSelection == 0) { // New game selected
					_inMainMenu = false;
					_paused = false; // Reiniciar el estado de pausa al empezar una nueva partida
				}
				else if (_mainMenuSelection == 1) { // Ranking selected
					// Handle ranking logic here
				}
				else if (_mainMenuSelection == 2) { // Exit selected
					_menuClosed = true;
				}
			}
		}
	}
	else {
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			_buffer.loadFromFile("assets/sounds/smw_save_menu.wav");
			_sound.setBuffer(_buffer);
			_sound.play();
			_paused = !_paused;
		}
		if (_paused && event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Down) {
				_pauseMenuSelection = (_pauseMenuSelection + 1) % 2; // Alternates between 0 and 1
			}
			else if (event.key.code == sf::Keyboard::Up) {
				_pauseMenuSelection = (_pauseMenuSelection + 1) % 2; // Alternates between 0 and 1
			}
			else if (event.key.code == sf::Keyboard::Enter) {
				if (_pauseMenuSelection == 1) { // Exit selected
					_inMainMenu = true;
					_paused = false;
				}
				else if (_pauseMenuSelection == 0) { // Continue selected
					_paused = false;
				}
			}
		}
	}
}

bool Director::shouldMenu() {
	return _menuClosed;
}

bool Director::shouldExit() {
	return _exitRequested;
}