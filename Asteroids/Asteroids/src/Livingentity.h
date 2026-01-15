#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Livingentity : public Entity
{
private:
	float speed = 0;
	int health = 1;

public:
	virtual ~Livingentity() = default;

	

	void setSpeed(float speed);
	float getSpeed() const;

	void setHealth(int health);
	int getHealth() const;

	void move(float dt);
};

