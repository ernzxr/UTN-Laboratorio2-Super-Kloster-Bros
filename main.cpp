#include "Director.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 640), "Super Kloster Bros");
	window.setFramerateLimit(60);

	std::unique_ptr<b2World> world;
	b2Vec2 gravity(0.0f, 980.0f);
	world = std::make_unique<b2World>(gravity);

	world->SetContactListener(new GlobalContactListener());

	Director director(*world);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else {
				director.update(event);
			}
		}

		if (director.shouldExit()) {
			window.close();
		}

		director.update();

		window.clear();

		director.render(window);

		window.display();
	}

	return 0;
}