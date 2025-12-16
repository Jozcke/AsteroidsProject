#include <SFML/graphics.hpp>
#include "Gamehandler.h"
#include "Renderwindow.h"
#include "Player.h"
#include "Bullet.h"
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
	deleteBullet(v_bullets, dt, window.getWindow());
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

void Gamehandler::deleteBullet(std::vector<Bullet>& v_bullets, float dt,const sf::RenderWindow& window)
{
	for (auto& bullet : v_bullets)
	{
		bullet.update(dt, window);
	}

	v_bullets.erase(
		std::remove_if(v_bullets.begin(), v_bullets.end(),
			[](const Bullet& b) {
				if (!b.isAlive())
					std::cout << "Bullet deleted" << std::endl;
					return !b.getAlive();
			}), v_bullets.end());
}