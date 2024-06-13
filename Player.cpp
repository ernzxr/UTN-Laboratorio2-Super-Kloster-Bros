#include "Player.h"
#include <iostream>

Player::Player(b2World& world, b2Vec2 position)
{
    // Define Body
    b2BodyDef bodyDef;
    bodyDef.position.Set((position.x + _width / 2.0f) / pixels_per_meter, (position.y + _height / 2.0f) / pixels_per_meter);
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = false;

    // Create Body
    _body = world.CreateBody(&bodyDef);

    // Create Shape
    b2PolygonShape b2shape;
    b2shape.SetAsBox(_width / 2.0f / pixels_per_meter, _height / 2.0f / pixels_per_meter);

    // Create Fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &b2shape;
    fixtureDef.density = 1.0f;

    // Attach Shape to Body
    _body->CreateFixture(&fixtureDef);

    // Create SFML Sprite
    _texture.loadFromFile("player.png");
    _sprite = new sf::Sprite();
    _sprite->setTexture(_texture);
    _sprite->setOrigin(_texture.getSize().x / 2.0f, _texture.getSize().y / 2.0f);

    _body->GetUserData().pointer = reinterpret_cast<uintptr_t>(_sprite);
}

void Player::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _velocity.x = _moveSpeed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _velocity.x = -_moveSpeed;
    }

    if (!_didJump) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            _didJump = true;
            _isJumping = true;
            _velocity.y += -30.0f;
        }
    }

    if (_didJump) {
        if (_velocity.y > -50.0f && _isJumping) {
            _velocity.y += -1.0f;
            if (_velocity.y == -50.0f) {
                _isJumping = false;
                _isFalling = true;
            }
        }
        if (_isFalling) {
            _velocity.y = 0.0f;
            _didJump = false;
            _isJumping = false;
            _isFalling = false;
        }
    }

    _body->SetLinearVelocity(_velocity);

    _velocity.x = 0.0f;

    std::cout << "{" << _velocity.x << ", " << _velocity.y << "}" << std::endl;
}
