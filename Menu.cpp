#include <iostream>
#include <string>
#include "Menu.h"
using namespace std;




void Menu::Jugar() {

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(60);


	b2Vec2 gravity(0.0f, 800.0f);
	b2World world(gravity);
	Player player(world, { 400,500 });

	Scene scene(world, &player);
	Map map(world);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					int opc;
					do {
						system("cls");					
						cout << "---PAUSA---" << endl;
						cout << "1 -CONTINUAR- " << endl;
						cout << "0 - SALIR " << endl;
						cout << "INGRESE OPCION " << endl;
						cin >> opc;
						switch (opc) {
						case 1:
							opc = 0;
							break;
						case 0:
							window.close();
						}
					} while (opc != 0);
					
				}
			}
		}
		scene.update();

		scene.render(window);
	}
	
}



void Menu::menu() {
	int opc;

	do {
		system("cls");
		cout << "Bienvenido" << endl;
		cout << "---MENU PRINCIPAL---" << endl;
		cout << "1 - JUGAR " << endl;
		cout << "0 - SALIR " << endl;
		cout << "INGRESE OPCION " << endl;
		cin >> opc;
		switch (opc) {
		case 1:
			system("cls");
			Jugar();
			break;
		case 0:
			system("cls");
			cout << "Gracias por Jugar" << endl;
		}
		system("pause");
	} while (opc != 0);


}