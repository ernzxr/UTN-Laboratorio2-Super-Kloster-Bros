#include "Player.h"
#include <iostream>

Player::Player(b2World& world, b2Vec2 position) : _startingPosition(position)
{
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

	//Enemy sensorFixture
	b2shape.SetAsBox(0.1f, 0.4f, b2Vec2(0.50f, 0.0f), 0.0f);
	fixtureDef.userData.pointer = (uintptr_t)&_fixtureData;
	fixtureDef.isSensor = true;
	_rightEnemyFixture = _body->CreateFixture(&fixtureDef);

	b2shape.SetAsBox(0.1f, 0.4f, b2Vec2(-0.50f, 0.0f), 0.0f);
	fixtureDef.userData.pointer = (uintptr_t)&_fixtureData;
	fixtureDef.isSensor = true;
	_leftEnemyFixture = _body->CreateFixture(&fixtureDef);

	//Top Ground Fixture
	b2shape.SetAsBox(0.4f, 0.1f, b2Vec2(-0.0f, -1.0f), 0.0f);
	fixtureDef.userData.pointer = (uintptr_t)&_fixtureData;
	fixtureDef.isSensor = true;
	_topFixture = _body->CreateFixture(&fixtureDef);

	// Create SFML Sprite
	_texture.loadFromFile("assets/SpriteSheetTimesTwo.png");
	_sprite = new sf::Sprite();
	_sprite->setTexture(_texture);
	_sprite->setTextureRect({ 64, 0 , 32, 64 });
	_sprite->setOrigin(_sprite->getGlobalBounds().width / 2.0f, _sprite->getGlobalBounds().height / 2.0f);
	_sprite->setScale(-1, 1);

	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(_sprite);
}

Player::~Player()
{
	_body->GetWorld()->DestroyBody(_body);
}

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
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))&& _onGround) {
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
			
			else if (_onRoof) {
				_velocity.y = -5.0f;
				_sprite->setTextureRect({ 64, 96, 32, 64 });
				_didJump = false;
				_isJumping = false;
				_isFalling = false;
				_onGround = false;
			}
			
		}
	}

	if (!isMoving) {
		_state = PlayerState::Idle;
	}
}

void Player::update()
{

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

	if (_sprite->getPosition().y >= 700) {
		_death = true;
	}
}

void Player::render(sf::RenderWindow& window) {
	_sprite->setPosition(_body->GetPosition().x * pixels_per_meter, _body->GetPosition().y * pixels_per_meter);
	_sprite->setRotation(_body->GetAngle() * deg_per_rad);
	window.draw(*_sprite);

	/*
	// Dibujar los fixtures para depuración
	drawFixture(_spikeFixture, window, sf::Color(255, 0, 0, 100)); // Rojo
	drawFixture(_groundFixture, window, sf::Color(0, 255, 0, 100)); // Verde
	drawFixture(_rightEnemyFixture, window, sf::Color(0, 0, 255, 100)); // Azul
	drawFixture(_leftEnemyFixture, window, sf::Color(0, 0, 255, 100)); // Azul
	drawFixture(_topFixture, window, sf::Color(255, 165, 0, 100)); // Naranja
	*/
}

void Player::drawFixture(b2Fixture* fixture, sf::RenderWindow& window, sf::Color color) {
	b2PolygonShape* shape = static_cast<b2PolygonShape*>(fixture->GetShape());
	b2Vec2 position = _body->GetPosition();
	sf::RectangleShape fixtureShape;
	fixtureShape.setSize(sf::Vector2f((shape->m_vertices[1].x - shape->m_vertices[0].x) * pixels_per_meter, (shape->m_vertices[2].y - shape->m_vertices[1].y) * pixels_per_meter));
	fixtureShape.setOrigin(fixtureShape.getSize().x / 2, fixtureShape.getSize().y / 2);
	fixtureShape.setPosition((position.x + shape->m_centroid.x) * pixels_per_meter, (position.y + shape->m_centroid.y) * pixels_per_meter);
	fixtureShape.setFillColor(color);
	window.draw(fixtureShape);
}

sf::Vector2f Player::getPosition() {
	b2Vec2 pos = _body->GetPosition();
	return sf::Vector2f(pos.x * pixels_per_meter, pos.y * pixels_per_meter);
}

void Player::onBeginContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData().pointer;

	if (!data) {
		return;
	}

	if (_spikeFixture == self && data->type == FixtureDataType::Spike) {
		_death = true;
	}
	else if (_groundFixture == self && (data->type == FixtureDataType::GroundTile || data->type == FixtureDataType::DestroyableTile)) {
		_onGround = true;
	}
	else if (self == _topFixture && (data->type == FixtureDataType::GroundTile || data->type == FixtureDataType::DestroyableTile)) {
		_onRoof = true;
	}
	else if((self == _rightEnemyFixture || self == _leftEnemyFixture) && data->type == FixtureDataType::Enemy) {
		_death = true;
	}
	else if (self != _groundFixture && self != _spikeFixture && data->type == FixtureDataType::Enemy) {
		_onGround = true;
	}
}

void Player::onEndContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData().pointer;

	if (!data) {
		return;
	}

	else if (_groundFixture == self && (data->type == FixtureDataType::GroundTile || data->type == FixtureDataType::DestroyableTile)) {
		_onGround = false;
	}
	else if (self == _topFixture && data->type == FixtureDataType::GroundTile) {
		_onRoof = false;
	}
	else if (self != _groundFixture && self != _spikeFixture && self == self && data->type == FixtureDataType::Enemy) {
		_onGround = false;
	}

}

bool Player::isDead() {
	return _death;
}
