#pragma once
#include "Credits.h"

Credits::Credits()
{
	_creditsTexture.loadFromFile("assets/CREDITS.png");
	_creditsSprite.setTexture(_creditsTexture);

	if (!_musicCredits.openFromFile("assets/sounds/creditsMusic.wav"))
		return; // error

	_musicCredits.setVolume(25.0f);

	_font.loadFromFile("assets/SuperMario256.ttf");
}

void Credits::update()
{
	if (_credits && _currentLineIndex < _vCredits.size()) {
		if (_clock.getElapsedTime().asSeconds() >= _timeBetweenLines) {
			_currentLineIndex++;
			_clock.restart();
		}
	}
}

void Credits::update(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed) {
		_selectedOption = true;
	}
}

void Credits::render(sf::RenderWindow& window)
{
	sf::View currentView = window.getView();
	sf::Vector2f centerPosition = currentView.getCenter();

	_creditsSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
	window.draw(_creditsSprite);

	if (_currentLineIndex < _vCredits.size()) {
		sf::Text text;
		text.setFont(_font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);
		text.setOutlineThickness(2);
		text.setOutlineColor(sf::Color::Black);
		text.setString(_vCredits[_currentLineIndex]);

		sf::FloatRect textoRect = text.getLocalBounds();
		text.setOrigin(textoRect.left + textoRect.width / 2.0f, textoRect.top + textoRect.height / 2.0f);
		text.setPosition(centerPosition.x, centerPosition.y);

		window.draw(text);
	}
	else {
		sf::Text text;
		text.setFont(_font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);
		text.setOutlineThickness(2);
		text.setOutlineColor(sf::Color::Black);
		text.setString("PRESIONA UNA TECLA PARA CONTINUAR");

		sf::FloatRect textoRect = text.getLocalBounds();
		text.setOrigin(textoRect.left + textoRect.width / 2.0f, textoRect.top + textoRect.height / 2.0f);
		text.setPosition(centerPosition.x, centerPosition.y);

		window.draw(text);
	}
}

bool Credits::getCredits() const
{
	return _credits;
}

bool Credits::creditsEnded() const
{
	return _selectedOption;
}

void Credits::open()
{
	_musicCredits.play();
	_credits = true;
	_selectedOption = false;
	_currentLineIndex = 0;
	_clock.restart();
}

void Credits::close()
{
	_musicCredits.stop();
	_credits = false;
}
