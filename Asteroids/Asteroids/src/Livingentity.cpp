#include "Livingentity.h"

sf::Vector2f Livingentity::getVelocity() const
{
	return this->velocity;
}

void Livingentity::setVelocity(sf::Vector2f swapVelocity)
{
	this->velocity = swapVelocity;
}

void Livingentity::setHealth(int health)
{
	this->health = health;
}

int Livingentity::getHealth() const
{
	return this->health;
}

void Livingentity::move(float dt)
{
	this->setPosition(getPosition() + velocity * dt);
}

float Livingentity::getSpeed() const
{
	return this->speed;
}

void Livingentity::setSpeed(float speed)
{
	this->speed = speed;
}