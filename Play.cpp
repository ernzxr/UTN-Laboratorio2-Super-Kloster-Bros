#pragma once
#include "Play.h"

Play::Play(b2World& world)
{
	_gameplay = new Gameplay(world);
}
void Play::update()
{
	_gameplay->update();
}

void Play::render(sf::RenderWindow& window)
{
	_gameplay->render(window);
}
