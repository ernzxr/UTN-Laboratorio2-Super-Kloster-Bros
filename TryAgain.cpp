#include "TryAgain.h"

TryAgain::TryAgain()
{
	_yesTexture.loadFromFile("assets/TRY_AGAIN_YES.png");
	_yesSprite.setTexture(_yesTexture);

	_noTexture.loadFromFile("assets/TRY_AGAIN_NO.png");
	_noSprite.setTexture(_noTexture);
}

void TryAgain::update(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Left) {
			_tryAgainSelection = (_tryAgainSelection + 1) % 2; // Alternates between 0 and 
		}
		else if (event.key.code == sf::Keyboard::Right) {
			_tryAgainSelection = (_tryAgainSelection + 1) % 2; // Alternates between 0 and 1
		}
		else if (event.key.code == sf::Keyboard::Enter) {
			if (_tryAgainSelection == 0) {
				_selectedOption = 0;
			}
			else if (_tryAgainSelection == 1) {
				_selectedOption = 1;
			}
		}
	}
}

void TryAgain::render(sf::RenderWindow& window)
{
	sf::View currentView = window.getView();
	sf::Vector2f centerPosition = currentView.getCenter();

	if (_tryAgainSelection == 0) {
		_yesSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
		window.draw(_yesSprite);
	}
	else if (_tryAgainSelection == 1) {
		_noSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
		window.draw(_noSprite);
	}
}

int TryAgain::getSelectedOption() const
{
	return _selectedOption;
}

bool TryAgain::getTryAgain() const
{
	return _tryAgain;
}

void TryAgain::open()
{
	_tryAgainSelection = 0;
	_selectedOption = -1;
	_tryAgain = true;
}

void TryAgain::close()
{
	_tryAgain = false;
}
