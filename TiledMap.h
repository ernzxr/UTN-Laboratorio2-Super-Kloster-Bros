#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "constants.h"
#include "GlobalContactListener.h"

class TiledMap
{
private:
    b2World& _world;

    // Temporal
    sf::RectangleShape* _shape;
    sf::RectangleShape* _structureShape;
    sf::RectangleShape* _structureShape2;
    sf::RectangleShape* _structureShape3;

    b2Body* _body;
    b2Body* _structure;
    b2Body* _structure2;
    b2Body* _structure3;
public:
    TiledMap(b2World& world);

    void render(sf::RenderWindow& window);

    void createFloor();

    void createStructure();
};
