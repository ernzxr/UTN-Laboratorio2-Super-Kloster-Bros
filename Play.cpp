#pragma once
#include "Play.h"

Play::Play(b2World& world) : _world(world)
{
	_gameplay = nullptr;
	_play = false;
	_pause = false;
}

void Play::update()
{
	_gameplay->update();
}

void Play::update(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			_pause = true;
		}
	}
}

void Play::render(sf::RenderWindow& window)
{
	_gameplay->render(window);
}

bool Play::getPlay() const
{
	return _play;
}

bool Play::getPause() const
{
	return _pause;
}

void Play::createGameplay()
{
	_gameplay = new Gameplay(_world);
}

void Play::newGame() {
	if (_gameplay != nullptr) {
		delete _gameplay;
	}
	createGameplay();
}

void Play::open()
{
	_pause = false;
	_play = true;
}

void Play::close()
{
	_play = false;
}
