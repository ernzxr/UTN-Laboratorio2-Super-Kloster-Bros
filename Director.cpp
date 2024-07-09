#include "Director.h"

Director::Director(b2World& world) {
	_scene = new Scene(world);
}

void Director::update() {
	_scene->update();
}

void Director::update(sf::Event event) {
	_scene->update(event);
}

void Director::render(sf::RenderWindow& window) {
	_scene->render(window);
}

bool Director::shouldExit() const {
	return _scene->shouldExit();
}