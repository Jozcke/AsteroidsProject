#pragma once

#include "Asteroid.h"
#include "Player.h"
#include "Bullet.h"
#include "SFML/Graphics.hpp"

class Collisionmanager
{

public:
	static bool circleCollision(const sf::Vector2f& aPos, float aRadius, const sf::Vector2f& bPos, float bRadius);
	
};

