#include "Entity.h"


void Entity::wrapAroundScreen(const sf::RenderWindow& window)
{
    sf::Vector2u size = window.getSize();

    if (position.x < 0.f)
        position.x = static_cast<float>(size.x);
    else if (position.x > size.x)
        position.x = 0.f;

    if (position.y < 0.f)
        position.y = static_cast<float>(size.y);
    else if (position.y > size.y)
        position.y = 0.f;
}

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