#include "Scene.h"
#include <iostream>

Scene::Scene(b2World& world)
{
	_menu = new Menu();
	_play = new Play(world);
	_pause = new Pause();
    _tryAgain = new TryAgain();
}

void Scene::update() {
    if (_play->getPlay()) {
        _play->update();
        if (_play->getTryAgain()) {
            _play->close();
            _tryAgain->open();
        }
        else if (_play->isGameFinished()) {
            _play->close();
            _menu->open();
        }
    }
}

void Scene::update(sf::Event event){
    if (_menu->getMainMenu())
    {
        _menu->update(event);
        if (_menu->getSelectedOption() == 0) {
            _menu->close();
            _play->newGame();
            _play->open();
        }
		else if (_menu->getSelectedOption() == 1) {
			_menu->close();
		}
        else if (_menu->getSelectedOption() == 2) {
            _menu->close();
        }
    }
    else if (_pause->getPaused())
    {
        _pause->update(event);
        if (_pause->getSelectedOption() == 0) {
            _pause->close();
            _play->open();
        }
        else if (_pause->getSelectedOption() == 1) {
            _pause->close();
            _menu->open();
        }
    }
    else if(_tryAgain->getTryAgain())
	{
		_tryAgain->update(event);
		if (_tryAgain->getSelectedOption() == 0) {
			_tryAgain->close();
			_play->tryAgain();
			_play->open();
		}
		else if (_tryAgain->getSelectedOption() == 1) {
			_tryAgain->close();
            _play->gameOver();
			_menu->open();
		}
	}
    else if (_play->getPlay())
    {
        _play->update(event);
        if (_play->getPause()) {
            _play->close();
            _pause->open();
        }
    }
}

void Scene::render(sf::RenderWindow& window)
{
	if (_menu->getMainMenu())
	{
		_menu->render(window);
	}
	else if (_tryAgain->getTryAgain())
	{
        _play->render(window);
		_tryAgain->render(window);
	}
	else if (_pause->getPaused())
	{
        _play->render(window);
		_pause->render(window);
	}
	else if (_play->getPlay())
	{
		_play->render(window);
	}
}

bool Scene::shouldExit() const
{
	return _menu->getShouldExit();
}
