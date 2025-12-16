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