#pragma once

#include "Rank.h"

Rank::Rank()
{
	_topTexture.loadFromFile("assets/RANKING_TOP.png");
	_topSprite.setTexture(_topTexture);

	_globalTexture.loadFromFile("assets/RANKING_GLOBAL.png");
	_globalSprite.setTexture(_globalTexture);
}

void Rank::update(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Left) {
			_rankMenuSelection = (_rankMenuSelection + 1) % 2; // Alternates between 0 and 
		}
		else if (event.key.code == sf::Keyboard::Right) {
			_rankMenuSelection = (_rankMenuSelection + 1) % 2; // Alternates between 0 and 1
		}
		else if (event.key.code == sf::Keyboard::Escape) {
			_selectedOption = 2;
		}
	}
}

void Rank::render(sf::RenderWindow& window)
{
	sf::View currentView = window.getView();
	sf::Vector2f centerPosition = currentView.getCenter();

	if (_rankMenuSelection == 0) {
		_topSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
		window.draw(_topSprite);
		_archivoRank.mostrarTopTen(window);
	}
	else if (_rankMenuSelection == 1) {
		_globalSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
		window.draw(_globalSprite);
	}
}

bool Rank::getRank() const
{
	return _inRank;
}

void Rank::open()
{
	_buffer.loadFromFile("assets/sounds/ranking.wav");
	_sound.setBuffer(_buffer);
	_sound.play();
	_archivoRank.ordenarRanking();
	_rankMenuSelection = 0;
	_selectedOption = -1;
	_inRank = true;
}

void Rank::close()
{
	_inRank = false;
}

int Rank::getSelectedOption() const
{
	return _selectedOption;
}
