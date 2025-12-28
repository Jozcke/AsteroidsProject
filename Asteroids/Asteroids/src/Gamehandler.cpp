#include <SFML/graphics.hpp>
#include "Gamehandler.h"
#include "Renderwindow.h"
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Collisionmanager.h"
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

	v_asteroid.reserve(10);
	v_bullets.reserve(10);
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
		
		if (player.getHealth() < 1)
		{
			gameReset();
		}
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
	AsteroidAsteroidCollision();
	
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
		Asteroid asteroid;
		sf::Vector2f spawnPos = randomEdgeSpawn(asteroid.getRadius());
		asteroid.setPosition({ spawnPos.x, spawnPos.y });

		if (validSpawnPosition({spawnPos.x, spawnPos.y}, asteroid.getRadius()))
		{
			v_asteroid.push_back(asteroid);
		}

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
			Asteroid asteroid;

			sf::Vector2f spawnPos = randomEdgeSpawn(asteroid.getRadius());
			asteroid.setPosition({ spawnPos.x, spawnPos.y });

			if (validSpawnPosition({ spawnPos.x, spawnPos.y }, asteroid.getRadius()))
			{
				v_asteroid.push_back(asteroid);
			}
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

void Gamehandler::AsteroidAsteroidCollision()
{
	for (size_t i = 0; i < v_asteroid.size(); i++)
	{
		for (size_t j = i + 1; j < v_asteroid.size(); j++)
		{
			if (Collisionmanager::circleCollision(v_asteroid[i].getPosition(), v_asteroid[i].getRadius(),
				v_asteroid[j].getPosition(), v_asteroid[j].getRadius()))
			{
				Collisionmanager::onCollisionVelocitySwap(v_asteroid[i], v_asteroid[j]);
			}
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

sf::Vector2f Gamehandler::randomEdgeSpawn(float radius)
{
	sf::Vector2u size = window.getWindow().getSize();

	float x, y;

	switch (rand() % 4) // rand 4 edges. 
	{
	case 0: // Top
		x = static_cast<float>(rand() % size.x);
		y = radius;
		break;

	case 1: // Bottom
		x = static_cast<float>(rand() % size.x);
		y = size.y - radius;
		break;

	case 2: // Left
		x = radius;
		y = static_cast<float>(rand() % size.y);
		break;

	default: // Right
		x = size.x - radius;
		y = static_cast<float>(rand() % size.y);
		break;
	}

	return { x, y };
}

bool Gamehandler::validSpawnPosition(const sf::Vector2f& pos,float radius)
{
	if (Collisionmanager::circleCollision(pos, radius, player.getPosition(), player.getRadius() + 50.f))
	{
		return false;
	}

	for (const auto& asteroid : v_asteroid)
	{
		if (Collisionmanager::circleCollision(pos, radius,asteroid.getPosition(), asteroid.getRadius()))
		{
			return false;
		}
	}

	return true;
}

void Gamehandler::gameReset()
{
	sf::Vector2u winSize = window.getWindow().getSize();
	sf::Vector2f windowCenter = { winSize.x / 2.f, winSize.y / 2.f };

	player.reset(windowCenter);

	v_asteroid.clear();
	v_bullets.clear();

	score = 0;
	spawnCooldown = 0.f;
	fireCooldown = 0.f;
	waveActive = false;
}