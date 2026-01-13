#include "Entity.h"

void Entity::setAlive(bool alive)
{
    this->alive = alive;
}

bool Entity::isAlive() const
{
    return this->alive;
}

void Entity::setPosition(const sf::Vector2f& pos)
{
    this->position = {pos};
}

sf::Vector2f Entity::getPosition() const
{
    return this->position;
}

void Entity::wrapAroundScreen(const sf::RenderWindow& window)
{
    sf::Vector2u size = window.getSize();

    if (position.x < -getRadius())
        position.x = size.x + getRadius();
    else if (position.x > size.x + getRadius())
        position.x = -getRadius();

    if (position.y < -getRadius())
        position.y = size.y + getRadius();
    else if (position.y > size.y + getRadius())
        position.y = -getRadius();
}