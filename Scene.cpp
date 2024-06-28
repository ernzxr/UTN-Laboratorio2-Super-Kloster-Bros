#include "Scene.h"

Scene::Scene(b2World& world, Player* player)
	: _world(world), _player(player) {
	if (_bgTexture.loadFromFile("assets/bg.jpg")) {
		_bgSprite.setTexture(_bgTexture);
	}
}


void Scene::update() {
	_player->update();
	_world.Step(1.0f / 60, int32(10), int32(8));
}
sf::Vector2f Scene::getCameraPosition() {

	return _player->getPosition();
}
void Scene::render(sf::RenderWindow& window) {

	window.clear();

	// Adjust the view to follow the player
	sf::View view = window.getView();
	sf::Vector2f playerPos = getCameraPosition();
	view.setCenter({ playerPos.x+150,300 });
	window.setView(view);

	// Draw the background
	_bgSprite.setPosition(0,0);
	window.draw(_bgSprite);

	// Draw the world
	displayWorld(window);

	window.display();
}

void Scene::displayWorld(sf::RenderWindow& render) {
	for (b2Body* body = _world.GetBodyList(); body != 0; body = body->GetNext()) {
		sf::Sprite* sprite = reinterpret_cast<sf::Sprite*>(body->GetUserData().pointer);
		sprite->setPosition(body->GetPosition().x * pixels_per_meter, body->GetPosition().y * pixels_per_meter);
		sprite->setRotation(body->GetAngle() * deg_per_rad);
		render.draw(*sprite);
	}
}