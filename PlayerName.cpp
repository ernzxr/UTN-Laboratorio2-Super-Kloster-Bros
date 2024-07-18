#include "PlayerName.h"

PlayerName::PlayerName()
{
    _playerNameTexture.loadFromFile("assets/PLAYER_NAME.png");
    _playerNameSprite.setTexture(_playerNameTexture);

	_font.loadFromFile("assets/SuperMario256.ttf");
}

void PlayerName::update(sf::Event event)
{
    if (_inPlayerName && event.type == sf::Event::TextEntered)
    {
        // Acepta letras minúsculas y mayúsculas, pero convierte las minúsculas a mayúsculas
        if ((event.text.unicode >= 'a' && event.text.unicode <= 'z') && _playerName.length() < 5)
        {
            // Convierte a mayúscula y agrega la letra al nombre del jugador
            _playerName += static_cast<char>(event.text.unicode - 32); // Convertir a mayúscula
        }
        else if ((event.text.unicode >= 'A' && event.text.unicode <= 'Z') && _playerName.length() < 5)
        {
            // Agrega la letra al nombre del jugador
            _playerName += static_cast<char>(event.text.unicode);
        }
        else if (event.text.unicode == 8 && !_playerName.empty()) // Tecla de retroceso
        {
            // Elimina la última letra del nombre del jugador
            _playerName.pop_back();
        }
        else if (event.text.unicode == 13 && !_playerName.empty()) // Tecla Enter
        {
            // Finaliza la entrada del nombre
            _setedPlayerName = true;
        }
    }
}

void PlayerName::render(sf::RenderWindow& window)
{
    sf::View currentView = window.getView();
    sf::Vector2f centerPosition = currentView.getCenter();

    _playerNameSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
    window.draw(_playerNameSprite);

    sf::Text label;
    label.setFont(_font);
    label.setCharacterSize(24);
    label.setFillColor(sf::Color::White);
    label.setOutlineThickness(2);
    label.setOutlineColor(sf::Color::Black);
    label.setString("INGRESA TU NOMBRE [MAX 5]:");
    // Calcula el ancho del texto
    sf::FloatRect textRect = label.getLocalBounds();
    // Ajusta la posición x para centrar el texto
    label.setPosition(centerPosition.x - textRect.width / 2, centerPosition.y - textRect.height / 2 - 20); // Posición ajustada para la etiqueta
    window.draw(label);

    // Ahora también mostramos el nombre del jugador que se está ingresando
    sf::Text playerNameText;
    playerNameText.setFont(_font);
    playerNameText.setCharacterSize(24);
    playerNameText.setFillColor(sf::Color::White);
    playerNameText.setOutlineThickness(2);
    playerNameText.setOutlineColor(sf::Color::Black);
    playerNameText.setString(_playerName); // Usamos _playerName para mostrar el nombre actual
    // Calcula el ancho del texto del nombre del jugador
    sf::FloatRect playerNameRect = playerNameText.getLocalBounds();
    // Ajusta la posición x para centrar el texto
    playerNameText.setPosition(centerPosition.x - playerNameRect.width / 2, centerPosition.y - playerNameRect.height / 2 + 10); // Posición para el nombre del jugador
    window.draw(playerNameText);
}

bool PlayerName::getInPlayerName() const
{
	return _inPlayerName;
}

std::string PlayerName::getPlayerName() const
{
	return _playerName;
}

bool PlayerName::setedPlayerName() const
{
	return _setedPlayerName;
}

void PlayerName::open()
{
	_inPlayerName = true;
    _setedPlayerName = false;
    _playerName.clear();
}

void PlayerName::close()
{
	_inPlayerName = false;
}
