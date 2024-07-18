#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gameplay.h"
class Rank
{
private:

	char nombrePlayer[30];
	int puntajePlayer;
	int intentos;
public:
	Rank();
	void cargarPlayer();
	bool grabarPlayer(Rank &obj);
	Rank leerPlayer(int pos);
	void mostrarRanking();
	int contarRegistros();
	void mostrarTopTen();
};