#include "Asteroid.h"
#include <random>

Asteroid::Asteroid()
{
	randomSize();
	setRadius(size);
	getShape(radius);
	setSpeed(size);
	setRandomDirection();
	
	hexagon.setFillColor(sf::Color::Transparent);
	hexagon.setOutlineColor(sf::Color::White);
	hexagon.setOutlineThickness(1.f);

	velocity = getSpeed() * getDirection();

	alive = true;

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

void Asteroid::setSpeed(int size)
{
	switch (size)
	{
	case 1: this->speed = 200.f; break;
	case 2: this->speed = 100.f; break;
	case 3: this->speed = 50.f; break;
	}
}

void Asteroid::draw(sf::RenderWindow& window)
{
	window.draw(this->hexagon);
}

void Asteroid::update(float dt, const sf::RenderWindow& window)
{
	position += velocity * dt;
	hexagon.setPosition(position);


}

float Asteroid::getSpeed() const
{
	return this->speed;
}

sf::Vector2f Asteroid::setRandomDirection() const
{
	float angle = static_cast<float>(rand()) / RAND_MAX * 2.f * 3.14159265f;
	sf::Vector2f direction(std::cos(angle),std::sin(angle));

	return direction;
}

sf::Vector2f Asteroid::getDirection() const
{
	return this->direction;
}