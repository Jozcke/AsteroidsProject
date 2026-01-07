#include "Asteroid.h"
#include <random>
#include "SFML/Graphics.hpp"

Asteroid::Asteroid() : Livingentity()
{
	randomSize();
	setRadius();
	setAsteroidSpeed();
	setRandomDirection();
	setHexagonShape();
	
	hexagon.setFillColor(sf::Color::Transparent);
	hexagon.setOutlineColor(sf::Color::White);
	hexagon.setOutlineThickness(1.f);

	this->setVelocity(getSpeed() * getDirection());
	this->setAlive(true);
	this->setHealth(1);

}

Asteroid::~Asteroid()
{

}

void Asteroid::randomSize()
{
	size =  rand() % 3 + 1;
}

void Asteroid::setRadius()
{
	switch (size)
	{
		case 1: this->radius = 15.f; break;
		case 2: this->radius = 30.f; break;
		case 3: this->radius = 50.f; break;
	}
}

void Asteroid::setHexagonShape()
{
	hexagon.setPointCount(6);
	
	for (size_t i = 0; i < 6; i++)
	{
		float angle = i * 60.f * 3.14159265f / 180.f;
		hexagon.setPoint(i, sf::Vector2f(
				std::cos(angle) * radius,
				std::sin(angle) * radius ));
	}
}

void Asteroid::setAsteroidSpeed()
{
	switch (size)
	{
		case 1: this->setSpeed(200.f); break;
		case 2: this->setSpeed(100.f); break;
		case 3: this->setSpeed(50.f); break;
	}
}

void Asteroid::draw(sf::RenderWindow& window)
{
	window.draw(this->hexagon);
}

void Asteroid::update(float dt, const sf::RenderWindow& window)
{
	this->move(dt);
	Entity::wrapAroundScreen(window);
	hexagon.setPosition(getPosition());
}

void Asteroid::setRandomDirection()
{
	float angle = static_cast<float>(rand()) / RAND_MAX * 2.f * 3.14159265f;
	direction = { std::cos(angle),std::sin(angle) };
}

sf::Vector2f Asteroid::getDirection() const
{
	return this->direction;
}

float Asteroid::getRadius() const
{
	return this->radius;
}

bool Asteroid::isAlive() const
{
	return this->Entity::isAlive();
}

void Asteroid::setAlive(bool alive)
{
	this->Entity::setAlive(alive);
}
