#include "Scene.h"

Scene::Scene(b2World& world)
{
	_menu = new Menu();
	_play = new Play(world);
	_pause = new Pause();
}

void Scene::update(bool _paused, int _pauseMenuSelection, bool _inMainMenu, int _mainMenuSelection)
{
	if (!_paused && !_inMainMenu)
	{
		_play->update();
	}
}

void Scene::render(sf::RenderWindow& window, bool _paused, int _pauseMenuSelection, bool _inMainMenu, int _mainMenuSelection)
{
	window.clear();

	if (_paused)
	{
		_pause->render(window, _pauseMenuSelection);
	}
	else if (_inMainMenu)
	{
		_menu->render(window, _mainMenuSelection);
	}
	else
	{
		_play->render(window);
	}

	window.display();
}