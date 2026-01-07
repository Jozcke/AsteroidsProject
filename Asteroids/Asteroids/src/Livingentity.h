#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Livingentity : public Entity
{
private:
	sf::Vector2f velocity = { 0.f, 0.f };
	float speed = 0;
	int health = 1;

public:
	virtual ~Livingentity() = default;

	sf::Vector2f getVelocity() const;
	void setVelocity(sf::Vector2f velocity);

	void setSpeed(float speed);
	float getSpeed() const;

	void setHealth(int health);
	int getHealth() const;

	void move(float dt);
};

