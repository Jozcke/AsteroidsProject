#include <SFML/graphics.hpp>
#include "Gamehandler.h"
#include "Renderwindow.h"
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include <iostream>
#include <algorithm>

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
		
		playerShooting(dt);
		
		///Draw objects here
		drawEntity();
		

	}

}


void Gamehandler::update(float dt)
{
	player.update(dt, window.getWindow());

	for (auto& asteroid : v_asteroid)
	{
		asteroid.update(dt, window.getWindow());
	}
	for (auto& bullet : v_bullets)
	{
		bullet.update(dt, window.getWindow());
	}
	deleteBullet();

}

void Gamehandler::drawEntity()
{
	
	window.clear(); // clear screen before drawing next frame
	//draw entities
	player.draw(window.getWindow());
	
	for (auto& bullet : v_bullets)
		bullet.draw(window.getWindow());

	for (auto& asteroid : v_asteroid)
		asteroid.draw(window.getWindow());
	

	//display drawn entities. 
	window.display();
}

void Gamehandler::playerShooting(float dt)
{
	fireCooldown -= dt;
	
	if (player.Shoot() && fireCooldown <= 0.f)
	{
		sf::Vector2f direction = player.shipForwardRotation();
		v_bullets.emplace_back(player.getPosition() + direction * 12.f, direction);
		fireCooldown = fireRate;
		std::cout << "Create bullet" << std::endl;
	}
}

void Gamehandler::deleteBullet()
{

	v_bullets.erase(
		std::remove_if(v_bullets.begin(), v_bullets.end(),
			[](const Bullet& b) {
				if (!b.isAlive())
				{
					std::cout << "Bullet deleted" << std::endl;
					return true;
				}
				return false;
			}), v_bullets.end());
}