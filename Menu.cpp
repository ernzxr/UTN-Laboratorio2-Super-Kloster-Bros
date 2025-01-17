#pragma once
#include "Menu.h"

Menu::Menu()
{
	_mainMenuSelection = 0;
	_selectedOption = -1;
	_inMainMenu = true;

	if (!_musicMenu.openFromFile("assets/sounds/menuMusic.wav"))
		return; // error

	_musicMenu.play();
	_musicMenu.setVolume(25.0f);
	_musicMenu.setLoop(true);

	_nuevaPTexture.loadFromFile("assets/NEW_GAME.png");
	_nuevaPSprite.setTexture(_nuevaPTexture);

	_rankingTexture.loadFromFile("assets/RANKING.png");
	_rankingSprite.setTexture(_rankingTexture);

	_salirTexture.loadFromFile("assets/SALIR.png");
	_salirSprite.setTexture(_salirTexture);
}

void Menu::update(sf::Event event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Down) {
			_mainMenuSelection = (_mainMenuSelection + 1) % 3; // Alternates between 0, 1, and 2
		}
		else if (event.key.code == sf::Keyboard::Up) {
			_mainMenuSelection = (_mainMenuSelection + 2) % 3; // Alternates between 0, 1, and 2
		}
		else if (event.key.code == sf::Keyboard::Enter) {
			if (_mainMenuSelection == 0) {
				_selectedOption = 0;
				_buffer.loadFromFile("assets/sounds/startGame.wav");
				_sound.setBuffer(_buffer);
				_sound.play();
			}
			else if (_mainMenuSelection == 1) {
				_selectedOption = 1;
			}
			else if (_mainMenuSelection == 2) {
				_selectedOption = 2;
			}
		}
	}
}

void Menu::render(sf::RenderWindow& window) {
	sf::View currentView = window.getView();
	sf::Vector2f centerPosition = currentView.getCenter();

	if (_mainMenuSelection == 0) {
		_nuevaPSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
		window.draw(_nuevaPSprite);
	}
	else if (_mainMenuSelection == 1) {
		_rankingSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
		window.draw(_rankingSprite);
	}
	else if (_mainMenuSelection == 2) {
		_salirSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
		window.draw(_salirSprite);
	}
}

bool Menu::getMainMenu() const
{
	return _inMainMenu;
}

bool Menu::getShouldExit() const
{
	if (_selectedOption == 2) {
		return true;
	}
	return false;
}

void Menu::open(bool music) {
	if (!music) {
		_musicMenu.play();
	}
	_mainMenuSelection = 0;
	_selectedOption = -1;
	_inMainMenu = true;
}

void Menu::close(bool music)
{
	if (!music) {
		_musicMenu.stop();
	}
	_inMainMenu = false;
}

int Menu::getSelectedOption() const
{
	return _selectedOption;
}
