#include <SFML/graphics.hpp>
#include "Gamehandler.h"
#include "Renderwindow.h"
#include "Player.h"
#include "Bullet.h"
#include <iostream>

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
		playerShooting();
		
		for (auto& bullet : v_bullets)
		{
			bullet.update(dt, window.getWindow());
		}
		///Draw objects here
		drawEntity();
		

	}

}


void Gamehandler::update(float dt)
{
	player.update(dt, window.getWindow());
	 
	v_bullets.erase(
	std::remove_if(v_bullets.begin(), v_bullets.end(),
	[](const Bullet& b) { return !b.isAlive(); }),
	v_bullets.end());
	std::cout << "delete bullet" << std::endl;
}

void Gamehandler::drawEntity()
{
	
	window.clear(); // clear screen before drawing next frame
	//draw entities
	player.draw(window.getWindow());
	
	for (auto& bullet : v_bullets)
		bullet.draw(window.getWindow());
	
	//display drawn entities. 
	window.display();
}



void Gamehandler::playerShooting()
{
	if (player.Shoot())
	{
		sf::Vector2f direction = player.shipForwardRotation();
		v_bullets.emplace_back(player.getPosition() + direction * 12.f, direction);
		std::cout << "Create bullet" << std::endl;
	}


}