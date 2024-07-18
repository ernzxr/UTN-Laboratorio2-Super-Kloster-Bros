#pragma
#include "Pause.h"

Pause::Pause()
{
	_continueTexture.loadFromFile("assets/CONTINUAR.png");
	_continueSprite.setTexture(_continueTexture);

	_exitTexture.loadFromFile("assets/PAUSA_SALIR.png");
	_exitSprite.setTexture(_exitTexture);

	_pauseMenuSelection = 0;
	_selectedOption = -1;
	_paused = false;
}

void Pause::update(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Down) {
			_pauseMenuSelection = (_pauseMenuSelection + 1) % 2; // Alternates between 0 and 
		}
		else if (event.key.code == sf::Keyboard::Up) {
			_pauseMenuSelection = (_pauseMenuSelection + 1) % 2; // Alternates between 0 and 1
		}
		else if (event.key.code == sf::Keyboard::Enter) {
			if (_pauseMenuSelection == 0) {
				_buffer.loadFromFile("assets/sounds/smw_save_menu.wav");
				_sound.setBuffer(_buffer);
				_sound.play();
				_selectedOption = 0;
			}
			else if (_pauseMenuSelection == 1) {
				_selectedOption = 1;
			}
		}
		else if (event.key.code == sf::Keyboard::Escape) {
			_buffer.loadFromFile("assets/sounds/smw_save_menu.wav");
			_sound.setBuffer(_buffer);
			_sound.play();
			_selectedOption = 0;
		}
	}
}

void Pause::render(sf::RenderWindow& window) {
	sf::View currentView = window.getView();
	sf::Vector2f centerPosition = currentView.getCenter();

	if (_pauseMenuSelection == 0) {
		_continueSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
		window.draw(_continueSprite);
	}
	else if (_pauseMenuSelection == 1) {
		_exitSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
		window.draw(_exitSprite);
	}
}

bool Pause::getPaused() const
{
	return _paused;
}

void Pause::open()
{
	_pauseMenuSelection = 0;
	_selectedOption = -1;
	_paused = true;
}

void Pause::close()
{
	_paused = false;
}

int Pause::getSelectedOption() const
{
	return _selectedOption;
}

