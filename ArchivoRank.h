#pragma once
#include <iostream>
#include "PlayerScore.h"
#include <SFML/Graphics.hpp>

class ArchivoRank
{
private:
	
public:
	ArchivoRank();

	bool grabarPlayer(const PlayerScore &obj);

	PlayerScore leerPlayer(int pos);

	int contarRegistros();

	void ordenarRanking();

	void mostrarTopTen(sf::RenderWindow& window);
};