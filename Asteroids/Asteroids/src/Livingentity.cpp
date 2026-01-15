#include "Livingentity.h"



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
	this->setPosition(getPosition() + Entity::getVelocity() * dt);
}

float Livingentity::getSpeed() const
{
	return this->speed;
}

void Livingentity::setSpeed(float speed)
{
	this->speed = speed;
}