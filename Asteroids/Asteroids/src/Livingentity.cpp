#include "Livingentity.h"

sf::Vector2f Livingentity::getVelocity() const
{
	return velocity;
}

void Livingentity::setVelocity(sf::Vector2f swapVelocity)
{
	this->velocity = swapVelocity;
}