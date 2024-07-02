#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Player.h"
#include "Scene.h"
#include "Director.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(60);

	b2Vec2 gravity(0.0f, 980.0f);
	b2World world(gravity);

	Director director(world);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			director.handleInput(event);
		}
		if (director.shouldExit()) {
			window.close();
		}

		director.update();

		director.render(window);
	}

	return 0;
}