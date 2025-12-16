#pragma once

#include <SFML/graphics.hpp>
#include "Renderwindow.h"
#include "Player.h"
#include "Bullet.h"
#include <vector>

class Gamehandler
{
private:
	Renderwindow window;
	Player player;
	std::vector<Bullet> v_bullets;
	float fireCooldown = 0.f;
	const float fireRate = 0.25f;





public:
	Gamehandler();
	~Gamehandler();
	

	void runGame();
	void drawEntity();
	void update(float dt);

	void playerShooting(float dt);
	void deleteBullet(std::vector<Bullet>& v_bullets, float dt, const sf::RenderWindow& window);
};