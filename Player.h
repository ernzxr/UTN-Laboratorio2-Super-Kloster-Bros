#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "constants.h"

class Player
{
private:
    sf::Texture _texture;
    sf::Sprite* _sprite;
    b2Body* _body;

    float _width = 50.0f;
    float _height = 68.0f;

    bool _isJumping = false;
    bool _isFalling = false;
    bool _isWalking = false;
    bool _isDucking = false;
    bool _didJump = false;

    b2Vec2 _velocity{0.0f , 0.0f};
    float _stateTime = 0.0f;
    float _moveSpeed = 10.0f;;
    float _jumpImpulse = -20.0f;
public:
    Player(b2World& world, b2Vec2 position);
    void update();
};

