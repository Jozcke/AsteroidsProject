#include <SFML/graphics.hpp>
#include "Gamehandler.h"
#include "Renderwindow.h"
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Collisionmanager.h"
#include "Scoremanager.h"
#include <iostream>
#include <algorithm>
#include <string>

Gamehandler::Gamehandler()
	: window(), healthText(gameFont), scoreText(gameFont), pauseText(gameFont), gameOverText(gameFont), nameInputText(gameFont), scoreManager(gameFont), gameState(GameState::Paused)
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
	scoreText.setPosition({ static_cast<float>(window.getSize().x) / 2.f , 10.f });

	pauseText.setFont(gameFont);
	pauseText.setCharacterSize(40);
	pauseText.setFillColor(sf::Color::Yellow);
	pauseText.setString("PAUSED");
	sf::FloatRect pauseTextBounds = pauseText.getLocalBounds();
	pauseText.setOrigin({ pauseTextBounds.size.x / 2.f, pauseTextBounds.size.y / 2.f});
	pauseText.setPosition({ static_cast<float>(window.getSize().x / 2.f),
						static_cast<float>(window.getSize().y - 100) });

	gameOverText.setFont(gameFont);
	gameOverText.setCharacterSize(40);
	gameOverText.setFillColor(sf::Color::Yellow);
	gameOverText.setString("GAME OVER");
	sf::FloatRect gameOverTextBounds = gameOverText.getLocalBounds();
	gameOverText.setOrigin({ gameOverTextBounds.size.x / 2.f, gameOverTextBounds.size.y / 2.f });
	gameOverText.setPosition({ static_cast<float>(window.getSize().x / 2.f),
						static_cast<float>(window.getSize().y - 100) });

	nameInputText.setFont(gameFont);
	nameInputText.setCharacterSize(30);
	nameInputText.setFillColor(sf::Color::White);

	sf::RectangleShape overlay;
	overlay.setSize(sf::Vector2f(window.getWindow().getSize()));
	overlay.setFillColor(sf::Color(0, 0, 0, 150));
	
	v_entity.reserve(30);


}

Gamehandler::~Gamehandler()
{
	for (Entity* entity : v_entity)
	{
		delete entity;
	}
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

			if (const auto keyPressed = event->getIf < sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::P && gameState != GameState::GameOver)
				{
					if (gameState == GameState::Paused)
					{
						gameState = GameState::Playing;
						std::cout << "Resume game." << std::endl;
					}
					else
					{
						gameState = GameState::Paused;
						std::cout << "Pause game" << std::endl;
					}
				}
			}
			if (gameState == GameState::GameOver && enterNameCheck)
			{
				if (const auto* charInput = event->getIf<sf::Event::TextEntered>())
				{	
					if (charInput->unicode == '\b' && !playerName.empty())
					{
						playerName.pop_back();
					}
					else if (charInput->unicode == '\r' && !playerName.empty())
					{
						scoreManager.addScore(playerName, score);
						scoreManager.saveScore("score/score.txt");

						gameReset();
						enterNameCheck = false;
						gameState = GameState::Paused;
						isGameOver = false;
					}
					else if (charInput->unicode < 128)
					{
						char c = static_cast<char>(charInput->unicode);

						if (std::isalnum(c))
						{
							if(playerName.size() < 10)
							{
								playerName += c;
							}
						}
					}				
				}
			}
		}

		//eventloop
		float dt = clock.restart().asSeconds();
		
		//updates position
		switch (gameState)
		{
		case Gamehandler::GameState::Playing:
			updateGame(dt);
			playerShooting(dt);
			spawnAsteroid(dt);
			break;
		
		case Gamehandler::GameState::GameOver:
			break;
		
		case Gamehandler::GameState::Paused:
			break;
		}
		
		drawEntity();
		
		if (player.getHealth() <= 0 && !isGameOver)
		{
			isGameOver = true;
			gameState = GameState::GameOver;

			if (scoreManager.checkifTopScore(score))
			{
				enterNameCheck = true;
				playerName.clear();
			}
			else
			{
				gameReset();
				gameState = GameState::Paused;
				isGameOver = false;
			}
		}
	}

}


void Gamehandler::updateGame(float dt)
{
	healthText.setString("Health " + std::to_string(player.getHealth()));
	scoreText.setString(std::to_string(getScore()));
	
	player.update(dt, window.getWindow());

	for (Entity* object : v_entity)
	{
		object->update(dt, window.getWindow());
	}
	
	bulletAsteroidCollision();
	AsteroidPlayerCollision();
	AsteroidAsteroidCollision();
	
	deleteDeadEntity();
	
	if (v_entity.empty())
	{
		waveActive = false;
	}
	spawnAsteroidsWhenEmpty(dt);

}

void Gamehandler::updatePause(float dt)
{

}

void Gamehandler::drawEntity()
{
	window.clear(); // clear screen before drawing next frame
	//draw entities
	player.draw(window.getWindow());
	
	for (Entity* object : v_entity)
		object->draw(window.getWindow());
	
	window.getWindow().draw(healthText);
	window.getWindow().draw(scoreText);
	
	
	if (gameState == GameState::Paused)
	{
		
		sf::RectangleShape overlay;
		overlay.setSize(sf::Vector2f(window.getWindow().getSize()));
		overlay.setFillColor(sf::Color(0, 0, 0, 150)); // semi-transparent black
		window.getWindow().draw(overlay);

		window.getWindow().draw(pauseText);
		scoreManager.draw(window.getWindow());
		
	}

	if (gameState == GameState::GameOver)
	{
		window.getWindow().draw(gameOverText);
		scoreManager.draw(window.getWindow());
		if (enterNameCheck)
		{
			nameInputText.setString("Name " + playerName + "_"); // underscore cursor
			// Center it horizontally
			sf::FloatRect bounds = nameInputText.getLocalBounds();
			nameInputText.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
			nameInputText.setPosition({ window.getWindow().getSize().x / 2.f,
				window.getWindow().getSize().y - 150.f });
			window.getWindow().draw(nameInputText);
		}
	}
	
	
	
	//display drawn entities. 
	window.display();
}

void Gamehandler::playerShooting(float dt)
{
	fireCooldown -= dt;
	
	if (player.Shoot() && fireCooldown <= 0.f)
	{
		sf::Vector2f direction = player.shipForwardRotation();
		v_entity.emplace_back(new Bullet(player.getPosition() + direction * player.getRadius(), direction));
		fireCooldown = fireRate;
		std::cout << "Create bullet" << std::endl;
	}
}


//could refactor the spawn function -> one function for spawn and spawn when empty.
//call the function in both functions -> only write it once. 
void Gamehandler::spawnAsteroid(float dt)
{
	spawnCooldown -= dt;

	if (spawnCooldown <= 0.f)
	{
		Asteroid* asteroid = new Asteroid();
		sf::Vector2f spawnPos = randomEdgeSpawn(asteroid->getRadius());
		asteroid->setPosition({ spawnPos });

		if (validSpawnPosition({spawnPos}, asteroid->getRadius()))
		{
			v_entity.push_back(asteroid);
		}
		else
		{
			delete asteroid;
		}

		spawnCooldown = spawnTime;
		std::cout << "asteroid created" << std::endl;
	}
}

void Gamehandler::spawnAsteroidsWhenEmpty(float dt)
{
	
	if (v_entity.empty() && waveActive != true)
	{
		int size = rand() % 8 + 3;
		for (size_t i = 0; i < size; i++)
		{
			Entity* asteroid = new Asteroid();

			sf::Vector2f spawnPos = randomEdgeSpawn(asteroid->getRadius());
			asteroid->setPosition({ spawnPos });

			if (validSpawnPosition({ spawnPos }, asteroid->getRadius()))
			{
				v_entity.push_back(asteroid);
			}
			else
			{
				delete asteroid;
			}
		}
		std::cout << "asteroid created" << std::endl;
		waveActive = true;
	}
}

void Gamehandler::deleteDeadEntity()
{
	v_entity.erase(std::remove_if(v_entity.begin(), v_entity.end(),
		[](Entity* object)
		{
			if (!object->isAlive())
			{
				delete object;
				std::cout << "object destroyed" << std::endl;
				return true;
			}
			return false;
		}),
		v_entity.end());
}

void Gamehandler::bulletAsteroidCollision()
{
	for (Entity* objectA : v_entity)
	{
		Bullet* bullet = dynamic_cast<Bullet*>(objectA);
		if (!bullet || !bullet->isAlive()) { continue; }

		for (Entity* objectB : v_entity)
		{
			Asteroid* asteroid = dynamic_cast<Asteroid*>(objectB);
			if (!asteroid || !asteroid->isAlive()) { continue; }

			if (Collisionmanager::circleCollision(
				bullet->getPosition(), bullet->getRadius(),
				asteroid->getPosition(), asteroid->getRadius()))
			{
				bullet->setAlive(false);
				asteroid->setAlive(false);
				addScore();
				return;
			}
		}
	}
}

void Gamehandler::AsteroidPlayerCollision()
{
	if (!player.isAlive()) {return;}
	
	for (Entity* objectA : v_entity)
	{
		Asteroid* asteroid = dynamic_cast<Asteroid*>(objectA);
		if (!asteroid || !asteroid->isAlive()) { continue; }
		
		if (Collisionmanager::circleCollision(
			player.getPosition(), player.getRadius(),
			asteroid->getPosition(), asteroid->getRadius()))
		{
				player.takeDamage(1);
				std::cout << "player hit by asteroid" << std::endl;
				asteroid->setAlive(false);
				break;
		}
	}
}

void Gamehandler::AsteroidAsteroidCollision()
{
	for (size_t i = 0; i < v_entity.size(); i++)
	{
		Asteroid* asteroidA = dynamic_cast<Asteroid*>(v_entity[i]);
		if (!asteroidA || !asteroidA->isAlive()) { continue; }
		
		for (size_t j = i+1; j < v_entity.size(); j++)
		{
			Asteroid* asteroidB = dynamic_cast<Asteroid*>(v_entity[j]);
			if (!asteroidB || !asteroidB->isAlive()) { continue; }
		

			if (Collisionmanager::circleCollision(
				asteroidA->getPosition(), asteroidA->getRadius(),
				asteroidB->getPosition(), asteroidB->getRadius()))
			{
				Collisionmanager::onCollisionVelocitySwap(*asteroidA, *asteroidB);
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

	switch (rand() % 4) // rand edges. 
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
	if (Collisionmanager::circleCollision(pos, radius, 
		player.getPosition(), player.getRadius() + 100.f))
	{
		return false;
	}

	for (const auto& asteroid : v_entity)
	{
		if (Collisionmanager::circleCollision(pos, radius,
			asteroid->getPosition(), asteroid->getRadius()))
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

	for (Entity* asteroid : v_entity)
	{
		delete asteroid;
	}
	
	v_entity.clear();


	score = 0;
	spawnCooldown = 0.f;
	fireCooldown = 0.f;
	waveActive = false;
}
