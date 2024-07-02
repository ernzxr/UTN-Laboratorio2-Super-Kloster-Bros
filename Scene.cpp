#include "Scene.h"
Scene::Scene(b2World& world, Player* player)
	: _world(world), _player(player) {
	if (_bgTexture.loadFromFile("assets/bg.jpg")) {
		_bgSprite.setTexture(_bgTexture);
	}
	_continueTexture.loadFromFile("assets/CONTINUE.jpg");
	_continueSprite.setTexture(_continueTexture);
	_continueSprite.setPosition(170.0f, 0.0f);
	
	_exitTexture.loadFromFile("assets/EXIT.jpg");
	_exitSprite.setTexture(_exitTexture);
	_exitSprite.setPosition(170.0f, 0.0f);
	
}

void Scene::displayWorld(sf::RenderWindow& render) {
	for (b2Body* body = _world.GetBodyList(); body != 0; body = body->GetNext()) {
		sf::Sprite* sprite = reinterpret_cast<sf::Sprite*>(body->GetUserData().pointer);
		sprite->setPosition(body->GetPosition().x * pixels_per_meter, body->GetPosition().y * pixels_per_meter);
		sprite->setRotation(body->GetAngle() * deg_per_rad);
		render.draw(*sprite);

	}
}

void Scene::update(){
	if (paused) {
		return;
	}
	//NEW
	_player->cmd();
	_player->update();
	_world.Step(1.0f / 60, int32(10), int32(8));
	_world.SetContactListener(new GlobalContactListener());
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

	if (paused) {
		if (pauseMenuSelection == 0) {
			window.draw(_continueSprite);
		}
		else if (pauseMenuSelection == 1) {
			window.draw(_exitSprite);
		}
	}

	

	window.display();
}

void Scene::handleInput(sf::Event event) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		paused = !paused;
	}
	if (paused && event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Down) {
			pauseMenuSelection = 1; // Alternates between 0 and 1
		}
		else if (event.key.code == sf::Keyboard::Up) {
			pauseMenuSelection = 0; // Alternates between 0 and 1
		}
		else if (event.key.code == sf::Keyboard::Enter) {
			if (pauseMenuSelection == 1) { // Exit selected
				exitRequested = true;
			}
			else if (pauseMenuSelection == 0) { // Continue selected
				paused = false;
			}
		}
	}
}
bool Scene::shouldExit() const {
	return exitRequested;
}
