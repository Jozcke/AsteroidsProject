#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
protected:
	sf::Vector2f position;
	bool alive = true;

public:
	virtual ~Entity() = default;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void update(float dt, const sf::RenderWindow& window) = 0;
	void wrapAroundScreen(const sf::RenderWindow& window);
	bool isAlive() const;
	void setAlive(bool alive);

	void setPosition(float posX, float posY);
	sf::Vector2f getPosition() const;
};

