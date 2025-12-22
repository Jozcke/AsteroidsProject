#pragma once

#include <SFML/graphics.hpp>
#include "Renderwindow.h"
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Collisionmanager.h"
#include <vector>

class Gamehandler
{
private:
	Renderwindow window;
	Player player;
	std::vector<Bullet> v_bullets;
	std::vector<Asteroid> v_asteroid;
	float fireCooldown = 0.f;
	const float fireRate = 0.25f;
	float spawnCooldown = 0.f;
	float spawnTime = 6.f;
	bool waveActive = true;
	int score = 0;

	sf::Font gameFont;
	sf::Text healthText;
	sf::Text scoreText;

public:
	Gamehandler();
	~Gamehandler();
	

	void runGame();
	void drawEntity();
	void update(float dt);

	void playerShooting(float dt);
	void deleteBullet();

	void spawnAsteroid(float dt);
	void spawnAsteroidsWhenEmpty(float dt);
	void deleteAsteroid();

	void bulletAsteroidCollision();
	void AsteroidPlayerCollision();

	int getScore() const;
	void addScore();
};