#pragma once
#include "Director.h"

Director::Director(b2World& world) : _world(world), _scene(_world) {
}

void Director::update()
{
	if (!_paused) {
		_scene.update();
	}
}

void Director::handleInput(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		_paused = !_paused;
	}
	if (_paused && event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Down) {
			_pauseMenuSelection = 1; // Alternates between 0 and 1
		}
		else if (event.key.code == sf::Keyboard::Up) {
			_pauseMenuSelection = 0; // Alternates between 0 and 1
		}
		else if (event.key.code == sf::Keyboard::Enter) {
			if (_pauseMenuSelection == 1) { // Exit selected
				_exitRequested = true;
			}
			else if (_pauseMenuSelection == 0) { // Continue selected
				_paused = false;
			}
		}
	}
}

bool Director::shouldExit() {
	return _exitRequested;
}

void Director::render(sf::RenderWindow& window)
{
	_scene.render(window, _paused, _pauseMenuSelection);
}