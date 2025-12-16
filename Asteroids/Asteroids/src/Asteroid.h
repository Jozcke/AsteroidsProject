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
	
	void randomSize();
	void getShape(float radius);
	void setRadius(int size);

public:
	Asteroid();
	~Asteroid();
	
};

