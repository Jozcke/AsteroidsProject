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
	void getShape(float radius);
	void setRadius(int size);
	void setSpeed(int size);

public:
	Asteroid();
	~Asteroid();
	void draw(sf::RenderWindow& window) override;
	void update(float dt, const sf::RenderWindow& window) override;
	float getSpeed() const;
	sf::Vector2f setRandomDirection() const;
	sf::Vector2f getDirection() const;

	
};

