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
		
		//updates position
		update(dt);
		
		///Draw objects here
		drawEntity();
		

	}

}


void Gamehandler::update(float dt)
{
	player.update(dt, window.getWindow());
}

void Gamehandler::drawEntity()
{
	
	window.clear(); // clear screen before drawing next frame
	//draw entities
	player.draw(window.getWindow());
	
	//display drawn entities. 
	window.display();
}