#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Livingentity : public Entity
{
protected:
	sf::Vector2f velocity;
	float speed = 0.f;
	int health;

public:
	virtual ~Livingentity() = default;
	void setPosition(const sf::Vector2f& pos) { position = pos; }
	sf::Vector2f getVelocity() const;
	void setVelocity(sf::Vector2f velocity);
};

