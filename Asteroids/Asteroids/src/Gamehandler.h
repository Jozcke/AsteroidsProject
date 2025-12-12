#pragma once

#include <SFML/graphics.hpp>
#include "Renderwindow.h"
#include "Player.h"


class Gamehandler
{
private:
	Renderwindow window;





public:
	Gamehandler();
	~Gamehandler();
	

	void runGame();
	//void drawentity();
	//void update();
};