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
	};
	sf::Font gameFont;
	
	Renderwindow window;
	Player player;
	Collisionmanager manager;
	GameState gameState;
	Scoremanager scoreManager;
	
	std::vector<Bullet> v_bullets;
	std::vector<Asteroid> v_asteroid;
	
	float fireCooldown = 0.f;
	const float fireRate = 0.25f;
	float spawnCooldown = 0.f;
	float spawnTime = 6.f;
	bool waveActive = true;
	int score = 0;

	sf::Text healthText;
	sf::Text scoreText;
	sf::Text pauseText;

public:
	Gamehandler();
	~Gamehandler();
	

	void runGame();
	void drawEntity();
	void updateGame(float dt);
	void updatePause(float dt);

	void playerShooting(float dt);
	void deleteBullet();

	void spawnAsteroid(float dt);
	void spawnAsteroidsWhenEmpty(float dt);
	sf::Vector2f randomEdgeSpawn(float radius);
	bool validSpawnPosition(const sf::Vector2f& pos, float radius);
	void deleteAsteroid();

	void bulletAsteroidCollision();
	void AsteroidPlayerCollision();
	void AsteroidAsteroidCollision();

	int getScore() const;
	void addScore();

	void gameReset();
};