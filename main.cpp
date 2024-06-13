#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

const float PI = 3.14159265359f;
const float pixels_per_meter = 32.0f;
const float deg_per_rad = 180.0f / PI;

inline b2Body* createFloor(b2World& world, sf::Texture& texture, float x, float y, float width, float height, b2BodyType type = b2_dynamicBody) {
	// Define Body
    b2BodyDef bodyDef;
    bodyDef.position.Set((x + width / 2.0f) / pixels_per_meter, (y + height / 2.0f) / pixels_per_meter);
	bodyDef.type = type;
    // bodyDef.linearDamping = 0.05f;

    // Create Body
    b2Body* body = world.CreateBody(&bodyDef);

    // Create Shape
    b2PolygonShape b2shape;
    b2shape.SetAsBox(width / 2.0f / pixels_per_meter, height / 2.0f / pixels_per_meter);

    // Create Fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &b2shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = .0f;

    // Attach Shape to Body
    body->CreateFixture(&fixtureDef);

	// Create SFML Shape
    sf::Sprite* sprite = new sf::Sprite();
    sprite->setTexture(texture);
    sprite->setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);

    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(sprite);

	return body;
}

inline b2Body* createPlayer(b2World& world, sf::Texture& texture, float x, float y, float width, float height, b2BodyType type = b2_dynamicBody) {
    // Define Body
    b2BodyDef bodyDef;
    bodyDef.position.Set((x + width / 2.0f) / pixels_per_meter, (y + height / 2.0f) / pixels_per_meter);
    bodyDef.type = type;
    // bodyDef.linearDamping = 0.05f;

    // Create Body
    b2Body* body = world.CreateBody(&bodyDef);

    // Create Shape
    b2PolygonShape b2shape;
    b2shape.SetAsBox(width / 2.0f / pixels_per_meter, height / 2.0f / pixels_per_meter);

    // Create Fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &b2shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = .0f;

    // Attach Shape to Body
    body->CreateFixture(&fixtureDef);

    // Create SFML Sprite
    sf::Sprite* sprite = new sf::Sprite();
    sprite->setTexture(texture);
    sprite->setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);

    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(sprite);

    return body;
}

inline void displayWorld(b2World& world, sf::RenderWindow& render) {
    world.Step(1.0f / 60, int32(6), int32(2));
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

    sf::Texture texture;
    texture.loadFromFile("player.png");

    sf::Texture floorTexture;
    floorTexture.loadFromFile("white-floor.png");

    b2Body* player = createPlayer(world, texture, 100, 492, 50, 68);

    for (int i = 0; i < 20; i++) {
        createFloor(world, floorTexture, i * 40, 560, 40, 40, b2_staticBody);
        if (i >= 15) {
            createFloor(world, floorTexture, i * 40, 360, 40, 40, b2_staticBody);
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        b2Vec2 velocity = player->GetLinearVelocity();
        float moveSpeed = 5.0f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocity.x = moveSpeed;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velocity.x = -moveSpeed;
        }
        else {
            velocity.x = 0.0f;  // Detener al jugador cuando no se presiona ninguna tecla de movimiento
        }

        // Aplicar velocidad al jugador
        player->SetLinearVelocity(velocity);

        window.clear();
        displayWorld(world, window);
        window.display();
    }

    return 0;
}