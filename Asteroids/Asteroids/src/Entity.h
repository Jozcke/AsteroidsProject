#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
private:
	sf::Vector2f position;
	bool alive = true;

public:
	virtual ~Entity() = default;
	
	
	virtual void update(float dt, const sf::RenderWindow& window) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	void wrapAroundScreen(const sf::RenderWindow& window);
	
	virtual bool isAlive() const;
	virtual void setAlive(bool alive);

	void setPosition(const sf::Vector2f& pos);
	sf::Vector2f getPosition() const;

	virtual float getRadius() const = 0;
};
