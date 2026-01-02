#include <iostream>
#include "SFML/graphics.hpp"
#include "Renderwindow.h"
#include "Gamehandler.h"
#include <string>


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(static_cast<unsigned int>(time(nullptr)));
	Gamehandler game;
	game.runGame();
}