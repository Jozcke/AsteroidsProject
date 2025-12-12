#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
private:

public:
	virtual ~Entity() = default;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void update(float dt, const sf::RenderWindow& window) = 0;


};

