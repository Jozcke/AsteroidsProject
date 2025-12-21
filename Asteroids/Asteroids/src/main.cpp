#include <iostream>
#include "SFML/graphics.hpp"
#include "Renderwindow.h"
#include "Gamehandler.h"
#include <string>


int main() {

	srand(time(0));
	Gamehandler game();
	game.runGame();
	
}