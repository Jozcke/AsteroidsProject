#pragma once

#include "Livingentity.h"
#include "SFML/Graphics.hpp"



class Asteroid : public Livingentity
{
private:
	sf::ConvexShape hexagon;
	int size;
	float rotationSpeed = 180.f;
	float speed;
	float radius;
	sf::Vector2f direction;
	
	void randomSize();
	void setHexagonShape();
	void setRadius();
	void setSpeed();

public:
	Asteroid();
	~Asteroid();
	
	void draw(sf::RenderWindow& window) override;
	void update(float dt, const sf::RenderWindow& window) override;
	
	float getSpeed() const;
	void setRandomDirection();
	sf::Vector2f getDirection() const;
	sf::Vector2f getPosition() const;
	float getRadius() const;
};

