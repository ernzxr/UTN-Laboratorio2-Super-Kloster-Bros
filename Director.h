#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Scene.h"
#include "Menu.h"
#include "Pause.h"

class Director {
private:
    b2World& _world;
    Scene _scene;
    Pause _pauseMenu;
    Menu _mainMenu;
    bool _paused;
    int _pauseMenuSelection;
    bool _exitRequested;
    bool _menuClosed;
    bool _inMainMenu;
    int _mainMenuSelection;
public:
    Director(b2World& world);
    void update();
    void handleInput(sf::Event event);
    bool shouldMenu();
    void render(sf::RenderWindow& window);
};