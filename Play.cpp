#pragma once
#include "Play.h"

Play::Play(b2World& world) : _world(world)
{
	if (!_musicMenu.openFromFile("assets/sounds/levelMusic.wav"))
		return; // error

	_musicMenu.setVolume(25.0f);
	_musicMenu.setLoop(true);
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

bool Play::getTryAgain()
{
	return _gameplay->getTryAgain();
}

bool Play::getCredits()
{
	return _gameplay->getCredits();
}

void Play::setPlayerName(std::string playerName)
{
	_gameplay->setPlayerName(playerName);
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

void Play::tryAgain() {
	_gameplay->tryAgain();
}

void Play::gameOver()
{
	_gameplay->gameOver();
}

void Play::gameWin()
{
	_gameplay->gameWin();
}

void Play::open()
{
	_musicMenu.play();
	_pause = false;
	_play = true;
}

void Play::close()
{
	_play = false;
	_musicMenu.stop();
}
