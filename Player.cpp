#include "Player.h"
#include <iostream>

Player::Player(b2World& world, b2Vec2 position) : _startingPosition(position)
{
    //NEW
    _fixtureData.listener = this;
    _fixtureData.player = this;
    _fixtureData.type = FixtureDataType::Player;

    // Define Body
    b2BodyDef bodyDef;
    bodyDef.position.Set((position.x + _width / 2.0f) / pixels_per_meter, (position.y + _height / 2.0f) / pixels_per_meter);
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;

    // Create Body
    _body = world.CreateBody(&bodyDef);

    // Create Shape
    b2PolygonShape b2shape;
    b2shape.SetAsBox(_width / 2.0f / pixels_per_meter, _height / 2.0f / pixels_per_meter);

    // Create Fixture
    b2FixtureDef fixtureDef;

    //NEW
    fixtureDef.shape = &b2shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.userData.pointer = (uintptr_t)&_fixtureData;
    _spikeFixture = _body->CreateFixture(&fixtureDef);

    // Attach Shape to Body
    _body->CreateFixture(&fixtureDef);

    // Sensor de colisiones para que no se ejecute el salto en bordes de paredes
    b2shape.SetAsBox(0.4f, 0.2f, b2Vec2(0.0f, 1.0f), 0.0f);
    fixtureDef.userData.pointer = (uintptr_t)&_fixtureData;
    fixtureDef.isSensor = true;
    _groundFixture = _body->CreateFixture(&fixtureDef);

    // Create SFML Sprite
    _texture.loadFromFile("assets/SpriteSheetTimesTwo.png");
    _sprite = new sf::Sprite();
    _sprite->setTexture(_texture);
    _sprite->setTextureRect({ 64, 0 , 32, 64 });
    _sprite->setOrigin(_sprite->getGlobalBounds().width / 2.0f, _sprite->getGlobalBounds().height / 2.0f);
    _sprite->setScale(-1, 1);

    _body->GetUserData().pointer = reinterpret_cast<uintptr_t>(_sprite);
}

//NEW
void Player::cmd()
{
    bool isMoving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _velocity.x = _moveSpeed;
        _state = PlayerState::Move;
        isMoving = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _velocity.x = -_moveSpeed;
        _state = PlayerState::Move;

        isMoving = true;
    }

    if (!_didJump) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _onGround) {
            _buffer.loadFromFile("assets/sounds/smw_jump.wav");
            _sound.setBuffer(_buffer);
            _sound.play();
            _didJump = true;
            _isJumping = true;
            isMoving = true;
            _velocity.y += -20.0f;
            _sprite->setTextureRect({ 0, 96, 32, 64 });
            _state = PlayerState::Jump;
        }
    }

    
    if (_didJump) {
        if (_velocity.y > -36.0f && _isJumping) {
            _velocity.y += -1.0f;
            if (_velocity.y <= -36.0f) {
                _isJumping = false;
                _isFalling = true;
                isMoving = true;
            }
        }
        if (_isFalling) {
            _velocity.y += 1.0f;
            isMoving = true;
            _sprite->setTextureRect({ 64, 96, 32, 64 });
            if (_velocity.y == 0) {
                _didJump = false;
                _isJumping = false;
                _isFalling = false;
            }
            /*
            else if (_onRoof) {
                _velocity.y = -5.0f;
                _sprite->setTextureRect({ 64, 96, 32, 64 });
                _didJump = false;
                _isJumping = false;
                _isFalling = false;
                _onGround = false;
            }
            */
        }
    }

    if (!isMoving) {
        _state = PlayerState::Idle;
    }
}

void Player::reset()
{
    _isReset = false;
    _isJumping = false;
    _isFalling = false;
    _isWalking = false;
    _isDucking = false;
    _didJump = false;
    _onGround = true;
    _stateTime = 0.0f;
    _velocity = { 0.0f , 0.0f };
    _frame = 0.0f;
    _moveSpeed = 10.0f;
    _state = PlayerState::Idle;
    _body->SetTransform(b2Vec2((_startingPosition.x + _width / 2.0f) / pixels_per_meter, (_startingPosition.y + _height / 2.0f) / pixels_per_meter), _body->GetAngle());
}

//NEW
void Player::update()
{   
    if (_isReset) {
        reset();
    }
    else {
        switch (_state) {
        case PlayerState::Idle:
            _sprite->setTextureRect({ 64, 0 , 32, 64 });
            break;
        case PlayerState::Move:
            _frame += 0.2f;

            if (_frame > 3) {
                _frame = 0;
            }

            if (!_isJumping && _onGround) {
                _sprite->setTextureRect({ 64 + int(_frame) * 64, 0 , 32, 64 });
            }

            if (_velocity.x < 0) {
                _sprite->setScale(1, 1);
            }
            else if (_velocity.x > 0) {
                _sprite->setScale(-1, 1);
            }
            break;
        }

        _body->SetLinearVelocity(_velocity);

        _velocity.x = 0.0f;
    }
    
    if (_sprite->getPosition().y >= 700) {
        reset();
    }

    std::cout << _onGround << std::endl;
}

void Player::render(sf::RenderWindow& window) {
    _sprite->setPosition(_body->GetPosition().x * pixels_per_meter, _body->GetPosition().y * pixels_per_meter);
    _sprite->setRotation(_body->GetAngle() * deg_per_rad);
    window.draw(*_sprite);
}

sf::Vector2f Player::getPosition() {
    b2Vec2 pos = _body->GetPosition();
    return sf::Vector2f(pos.x * pixels_per_meter, pos.y * pixels_per_meter);
}

//NEW
void Player::onBeginContact(b2Fixture* self, b2Fixture* other)
{
    FixtureData* data = (FixtureData*)other->GetUserData().pointer;

    if (!data) {
        return;
    }

    if (_spikeFixture == self && data->type == FixtureDataType::Spike) {
        _isReset = true;
    }
    else if (_groundFixture == self && data->type == FixtureDataType::GroundTile) {
        _onGround = true;
    }
    else if (_groundFixture == self && data->type == FixtureDataType::Enemy) {
        _onGround = true;
    }
}

void Player::onEndContact(b2Fixture* self, b2Fixture* other)
{
    FixtureData* data = (FixtureData*)other->GetUserData().pointer;

    if (!data) {
        return;
    }

    if (_spikeFixture == self && data->type == FixtureDataType::Spike) {
        _isReset = true;
    }
    else if (_groundFixture == self && data->type == FixtureDataType::GroundTile) {
        _onGround = false;
    }
    else if (_groundFixture == self && data->type == FixtureDataType::Enemy) {
        _onGround = false;
    }

}