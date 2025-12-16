#include "Asteroid.h"
#include <random>

Asteroid::Asteroid()
{
	randomSize();
	setRadius(size);
	getShape(radius);
	
	hexagon.setFillColor(sf::Color::Transparent);
	hexagon.setOutlineColor(sf::Color::White);
	hexagon.setOutlineThickness(1.f);
}

Asteroid::~Asteroid()
{

}

void Asteroid::randomSize()
{
	size =  rand() % 3 + 1;
}

void Asteroid::setRadius(int size)
{
	switch (size)
	{
	case 1: this->radius = 15.f; break;
	case 2: this->radius = 30.f; break;
	case 3: this->radius = 50.f; break;
	}
}

void Asteroid::getShape(const float radius)
{
	hexagon.setPointCount(6);
	
	for (size_t i = 0; i < 6; i++)
	{
		float angle = i * 60.f * 3.14159265f / 180.f;
		hexagon.setPoint(i, sf::Vector2f(
				std::cos(angle) * radius,
				std::sin(angle) * radius
			)
		);
	}
}