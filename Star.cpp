#include "Star.h"

Star::Star(b2World& world, b2Vec2 position, int points, StarType type) : _points(points), _starType(type)
{
    // Define Body
    b2BodyDef bodyDef;
    bodyDef.position.Set((position.x + _width / 2.0f) / pixels_per_meter, (position.y + _height / 2.0f) / pixels_per_meter);
    bodyDef.type = b2_staticBody;

    // Create Body
    _body = world.CreateBody(&bodyDef);

    // Create Shape
    b2PolygonShape b2shape;
    b2shape.SetAsBox(_width / 2.0f / pixels_per_meter, _height / 2.0f / pixels_per_meter);

    // Type of Fixture Data
    _fixtureData.listener = this;
    _fixtureData.type = FixtureDataType::Star;

    // Create Fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &b2shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.userData.pointer = (uintptr_t)&_fixtureData;

    // Attach Shape to Body
    _body->CreateFixture(&fixtureDef);

    // Create SFML Sprite
    _texture.loadFromFile("assets/SpriteSheetTimesTwo.png");
    _sprite = new sf::Sprite();
    _sprite->setTexture(_texture);
    _sprite->setTextureRect({ 0, 384 , 32, 32 });
    _sprite->setOrigin(_sprite->getGlobalBounds().width / 2.0f, _sprite->getGlobalBounds().height / 2.0f);
    _sprite->setScale(-1, 1);

    _body->GetUserData().pointer = reinterpret_cast<uintptr_t>(_sprite);
}

Star::~Star()
{
	_body->GetWorld()->DestroyBody(_body);
    delete _sprite;
}

void Star::update()
{
    _frame += 0.1f;

    if (_frame > 4) {
        _frame = 0;
    }

    _sprite->setTextureRect({ 0 + (int)_frame * 32, 384, 24, 32 });
}

void Star::render(sf::RenderWindow& window)
{
    _sprite->setPosition(_body->GetPosition().x * pixels_per_meter, _body->GetPosition().y * pixels_per_meter);
    _sprite->setRotation(_body->GetAngle() * deg_per_rad);
    window.draw(*_sprite);
}

int Star::getPoints() const
{
    return _points;
}

bool Star::isCollected() const
{
    return _isCollected;
}

bool Star::isWinStar() const
{
    if (_starType == StarType::Win) {
		return true;
	}
    return false;
}

void Star::onBeginContact(b2Fixture* self, b2Fixture* other)
{
    FixtureData* data = (FixtureData*)other->GetUserData().pointer;

	if (data->type == FixtureDataType::Player) {
		_isCollected = true;
	}
}

void Star::onEndContact(b2Fixture* self, b2Fixture* other)
{
    FixtureData* data = (FixtureData*)other->GetUserData().pointer;
}
