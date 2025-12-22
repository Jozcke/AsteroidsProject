#include <SFML/graphics.hpp>
#include "Gamehandler.h"
#include "Renderwindow.h"
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include <iostream>
#include <algorithm>
#include <string>

Gamehandler::Gamehandler()
	: window(), healthText(gameFont), scoreText(gameFont)
{
	if (!gameFont.openFromFile("font/ARCADECLASSIC.TTF")) {
		std::cerr << "Failed to load font!" << std::endl;
	}
	sf::Vector2u size = window.getSize();

	healthText.setFont(gameFont);
	healthText.setCharacterSize(30);
	healthText.setFillColor(sf::Color::White);
	healthText.setPosition({ 10.f, 10.f });


	scoreText.setFont(gameFont);
	scoreText.setCharacterSize(30);
	scoreText.setFillColor(sf::Color::White);
	
	sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
	scoreText.setOrigin({ scoreTextBounds.size.x, scoreTextBounds.size.y });
	scoreText.setPosition({ static_cast<float>(window.getSize().x) / 2, 10.f });
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
		spawnAsteroid(dt);
		
		///Draw objects here
		drawEntity();
		

	}

}


void Gamehandler::update(float dt)
{
	healthText.setString("Health " + std::to_string(player.getHealth()));
	scoreText.setString(std::to_string(getScore()));
	
	player.update(dt, window.getWindow());

	for (auto& asteroid : v_asteroid)
	{
		asteroid.update(dt, window.getWindow());
	}
	
	for (auto& bullet : v_bullets)
	{
		bullet.update(dt, window.getWindow());
	}
	
	bulletAsteroidCollision();
	AsteroidPlayerCollision();
	deleteBullet();
	deleteAsteroid();
	
	if (v_asteroid.empty())
	{
		waveActive = false;
	}
	spawnAsteroidsWhenEmpty(dt);

}

void Gamehandler::drawEntity()
{
	
	window.clear(); // clear screen before drawing next frame
	//draw entities
	player.draw(window.getWindow());
	
	window.getWindow().draw(healthText);
	window.getWindow().draw(scoreText);
	
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
	v_bullets.erase(std::remove_if(v_bullets.begin(), v_bullets.end(),
			[](const Bullet& b) {
				if (!b.isAlive())
				{
					std::cout << "Bullet deleted" << std::endl;
					return true;
				}
				return false;
			}), v_bullets.end());
}

void Gamehandler::spawnAsteroid(float dt)
{
	spawnCooldown -= dt;
	
	if (spawnCooldown <= 0.f)
	{
		v_asteroid.push_back(Asteroid());
		spawnCooldown = spawnTime;
		std::cout << "asteroid created" << std::endl;
	}
}

void Gamehandler::spawnAsteroidsWhenEmpty(float dt)
{
	
	if (v_asteroid.size() < 1 && waveActive != true)
	{
		int size = rand() % 5 + 1;
		for (size_t i = 0; i < size; i++)
		{
			v_asteroid.emplace_back(Asteroid());
		}
		std::cout << "asteroid created" << std::endl;
		waveActive = true;
	}
}

void Gamehandler::deleteAsteroid()
{
	v_asteroid.erase(std::remove_if(v_asteroid.begin(), v_asteroid.end(),
			[](const Asteroid& a) { 
				if (!a.isAlive())
				{
					std::cout << "Asteroid destroyed" << std::endl;
					return true;
				}
				return false;
			}), v_asteroid.end());
}

void Gamehandler::bulletAsteroidCollision()
{
	for (auto& bullet : v_bullets)
	{
		for (auto& asteroid : v_asteroid)
		{
			if (!asteroid.isAlive()) {continue;}
			if (Collisionmanager::circleCollision(bullet.getPosition(), bullet.getRadius(),
				asteroid.getPosition(), asteroid.getRadius()))
			{
				bullet.setAlive(false);
				asteroid.setAlive(false);
				addScore();
				break;  //fail-safe break incase bullet might register more than 1 collision. 
			}
		}
	}
}

void Gamehandler::AsteroidPlayerCollision()
{
	if (!player.isAlive()) {return;}
	
	for (auto& asteroid : v_asteroid)
	{
		if (Collisionmanager::circleCollision(player.getPosition(), player.getRadius(),
			asteroid.getPosition(), asteroid.getRadius()))
		{
				player.takeDamage(1);
				//if (player.getHealth() <= 0) { player.setAlive(false); }
				std::cout << "player hit by asteroid" << std::endl;
				asteroid.setAlive(false);
				break;
		}
	}
}

int Gamehandler::getScore() const
{
	return this->score;
}

void Gamehandler::addScore()
{
	this->score += 10;
}