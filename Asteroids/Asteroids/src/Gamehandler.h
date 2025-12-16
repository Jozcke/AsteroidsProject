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





public:
	Gamehandler();
	~Gamehandler();
	

	void runGame();
	void drawEntity();
	void update(float dt);

	void playerShooting();
};