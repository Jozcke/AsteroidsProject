#include <SFML/graphics.hpp>
#include "Gamehandler.h"
#include "Renderwindow.h"
#include "Player.h"

Gamehandler::Gamehandler()
	: window()
{
}

Gamehandler::~Gamehandler()
{
}

void Gamehandler::runGame()
{
	
	Player player;
	sf::Clock clock;
	
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
		float dt = clock.restart().asSeconds();
		player.update(dt,window.getWindow());
		
		
		

		window.clear();
		///Draw objects here
		player.draw(window.getWindow());
		window.display();

		

	}

}
