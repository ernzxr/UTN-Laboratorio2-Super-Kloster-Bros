#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Scene.h"
#include "Menu.h"
#include "Pause.h"

class Director {
private:
    Scene* _scene;
public:
    Director(b2World& world);

    void update();

    void update(sf::Event event);

    void render(sf::RenderWindow& window);

    bool shouldExit() const;
};