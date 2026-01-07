#pragma once

#include "Livingentity.h"
#include "SFML/Graphics.hpp"



class Asteroid : public Livingentity
{
private:
	sf::ConvexShape hexagon;
	sf::Vector2f direction;
	int size;
	float radius;
	
	
	void randomSize();
	void setHexagonShape();
	void setRadius();
	void setAsteroidSpeed();
	void setRandomDirection();

public:
	Asteroid();
	~Asteroid();
	
	void draw(sf::RenderWindow& window) override;
	void update(float dt, const sf::RenderWindow& window) override;

	sf::Vector2f getDirection() const;
	float getRadius() const override;

	bool isAlive() const override;
	void setAlive(bool alive) override;
};

