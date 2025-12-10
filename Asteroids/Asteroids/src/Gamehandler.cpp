#include <SFML/graphics.hpp>
#include "Gamehandler.h"
#include "Renderwindow.h"

Gamehandler::Gamehandler()
	: window()
{
}

Gamehandler::~Gamehandler()
{
}

void Gamehandler::runGame()
{
	while (window.isOpen())
	{
		while (auto event = this->window.pollEventWindow())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
		//eventloop

		window.clear();
		///Draw objects here
		window.display();

		

	}

}
