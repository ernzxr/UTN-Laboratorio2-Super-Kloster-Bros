#include "Enemy.h"
#include <iostream>

Enemy::Enemy(b2World& world, b2Vec2 position)
{
    _fixtureData.listener = this;
    _fixtureData.enemy = this;
    _fixtureData.type = FixtureDataType::Enemy;

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
    fixtureDef.shape = &b2shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.userData.pointer = (uintptr_t)&_fixtureData;

    // Attach Shape to Body
    _body->CreateFixture(&fixtureDef);
    
    // Sensor de colisiones para que no se ejecute el salto en bordes de paredes
    b2shape.SetAsBox(0.4f, 0.2f, b2Vec2(0.0f, 1.0f), 0.0f);
    fixtureDef.userData.pointer = (uintptr_t)&_fixtureData;
    fixtureDef.isSensor = true;
    _body->CreateFixture(&fixtureDef);
    
    // Create SFML Sprite
    _texture.loadFromFile("assets/SpriteSheetTimesTwo.png");
    _sprite = new sf::Sprite();
    _sprite->setTexture(_texture);
    _sprite->setTextureRect({ 0, 170 , 32, 52 });
    _sprite->setOrigin(_sprite->getGlobalBounds().width / 2.0f, _sprite->getGlobalBounds().height / 2.0f);
    _sprite->setScale(-1, 1);

    _body->GetUserData().pointer = reinterpret_cast<uintptr_t>(_sprite);
}

Enemy::~Enemy()
{
    _body->GetWorld()->DestroyBody(_body);
}

void Enemy::update()
{
    _frame += 0.1f;

    if (_frame > 2) {
        _frame = 0;
    }

    _sprite->setTextureRect({ 0 + (int)_frame * 64, 170, 32, 52 });

    _velocity = _body->GetLinearVelocity();

    if (std::abs(_velocity.x) <= 0.02f) {
        _moveSpeed *= -1.0f;
    }

    if (_velocity.x < 0) {
        _sprite->setScale(1, 1);
    }
    else if (_velocity.x > 0) {
        _sprite->setScale(-1, 1);
    }

    _velocity.x = _moveSpeed;

    _body->SetLinearVelocity(_velocity);


    if (_isDead) {
        _deathTimer += 0.07f;
        _sprite->setTextureRect({ 112, 208, 32, 16 });

        _sprite->setOrigin(_sprite->getGlobalBounds().width / 2.0f, _sprite->getGlobalBounds().height * -1.0f);

        if (_deathTimer >= 1) {
            _body->SetTransform(b2Vec2(_body->GetPosition().x, 1000.0f / pixels_per_meter), _body->GetAngle());
            _deathTimer = 0.0f;
            return;
        }
    }
}

void Enemy::render(sf::RenderWindow& window)
{
    _sprite->setPosition(_body->GetPosition().x * pixels_per_meter, _body->GetPosition().y * pixels_per_meter);
    _sprite->setRotation(_body->GetAngle() * deg_per_rad);
    window.draw(*_sprite);
}

void Enemy::onBeginContact(b2Fixture* self, b2Fixture* other)
{
    FixtureData* data = (FixtureData*)other->GetUserData().pointer;

    if (data && data->type == FixtureDataType::Player) {
            _isDead = true;
    }

}

void Enemy::onEndContact(b2Fixture* self, b2Fixture* other)
{
    FixtureData* data = (FixtureData*)other->GetUserData().pointer;
}
