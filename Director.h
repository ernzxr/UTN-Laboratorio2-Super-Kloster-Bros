#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Scene.h"
#include "Menu.h"
#include "Pause.h"

class Director {
private:
    Scene* _scene;

    bool _paused;
    int _pauseMenuSelection;

    bool _inMainMenu;
    int _mainMenuSelection;

    bool _exitRequested;
    bool _menuClosed;
public:
    Director(b2World& world);

    void update();

    void render(sf::RenderWindow& window);

    void handleInput(sf::Event event);

    bool shouldMenu();

    bool shouldExit();
};