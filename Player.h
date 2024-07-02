#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "constants.h"
#include "GlobalContactListener.h"

enum class PlayerState {
    Idle = 0,
    Move,
    Jump,
};


class Player : public ContactListener
{
private:
    sf::Texture _texture;
    sf::Sprite* _sprite;
    b2Body* _body;

    float _width = 32.0f;
    float _height = 64.0f;

    bool _isJumping = false;
    bool _isFalling = false;
    bool _isWalking = false;
    bool _isDucking = false;
    bool _didJump = false;

    b2Vec2 _velocity{0.0f , 0.0f};
    float _moveSpeed = 10.0f;

    float _stateTime = 0.0f;

    float _frame = 0.0f;

    PlayerState _state = PlayerState::Idle;

    bool _onGround = false;

    FixtureData _fixtureData;
public:
    Player(b2World& world, b2Vec2 position);
    void update();
    void render(sf::RenderWindow& window);
    sf::Vector2f getPosition();
    void cmd();

    virtual void onBeginContact(b2Fixture* other) override;
    virtual void onEndContact(b2Fixture* other) override;
};

