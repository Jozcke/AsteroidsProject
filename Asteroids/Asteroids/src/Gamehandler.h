#pragma once

#include <SFML/graphics.hpp>
#include "Renderwindow.h"



class Gamehandler
{
private:
	Renderwindow window;





public:
	Gamehandler();
	~Gamehandler();
	

	void runGame();
};