#pragma once

#include <SFML/graphics.hpp>
#include "Renderwindow.h"
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Collisionmanager.h"
#include "Scoremanager.h"
#include <vector>

class Gamehandler
{
private:
	enum class GameState
	{
		Playing,
		GameOver,
		Paused,
		MainMenu,
	};
	
	sf::Font gameFont;
	
	Renderwindow window;
	Player player;
	Collisionmanager manager;
	GameState gameState;
	Scoremanager scoreManager;
	
	std::vector<Entity*> v_entity;  //vector for bullets & asteroids
	
	float fireCooldown = 0.f;
	const float fireRate = 0.25f;
	float spawnCooldown = 0.f;
	float spawnTime = 4.f;
	bool waveActive = true;
	bool isGameOver = false;
	int score = 0;

	sf::Text healthText;
	sf::Text scoreText;
	sf::Text pauseText;
	sf::Text gameOverText;
	sf::Text nameInputText;
	sf::Text MenuAsteroidText;
	sf::Text pressToStartText;

	std::string playerName;
	bool enterNameCheck = false;

public:
	Gamehandler();
	~Gamehandler();
	

	void runGame();
	void drawEntity();
	void updateGame(float dt);

	void playerShooting(float dt);

	void spawnAsteroid(float dt);
	void spawnAsteroidsWhenEmpty(float dt);
	sf::Vector2f randomEdgeSpawn(float radius);
	bool validSpawnPosition(const sf::Vector2f& pos, float radius);
	
	void deleteDeadEntity();

	void bulletAsteroidCollision();
	void AsteroidPlayerCollision();
	void AsteroidAsteroidCollision();

	int getScore() const;
	void addScore();

	void gameReset();
};