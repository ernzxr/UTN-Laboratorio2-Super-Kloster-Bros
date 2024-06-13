#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Player.h"
#include "Map.h"

inline void displayWorld(b2World& world, sf::RenderWindow& render) {
    world.Step(1.0f / 60, int32(10), int32(8));
    for (b2Body* body = world.GetBodyList(); body != 0; body = body->GetNext()) {
        sf::Sprite* sprite = reinterpret_cast<sf::Sprite*>(body->GetUserData().pointer);
        sprite->setPosition(body->GetPosition().x * pixels_per_meter, body->GetPosition().y * pixels_per_meter);
        sprite->setRotation(body->GetAngle() * deg_per_rad);
        render.draw(*sprite);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(60);

    b2Vec2 gravity(0.0f, 9.81f);
    b2World world(gravity);

    Player player(world, {100, 492});
    Map map(world);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.update();

        window.clear();

        displayWorld(world, window);

        window.display();
    }

    return 0;
}