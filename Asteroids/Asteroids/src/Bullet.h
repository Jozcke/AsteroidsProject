#pragma once
#include "Entity.h"
#include "Player.h"
#include "SFML/Graphics.hpp"



class Bullet : public Entity
{
private:
	sf::CircleShape shapeBullet;
	sf::Vector2f velocity;
	static constexpr float BULLETSPEED = 400.f;

public:
	Bullet(const sf::Vector2f& startPosition, const sf::Vector2f& direction);
	~Bullet();
	void update(float dt, const sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window) override;
	float getRadius() const;
	sf::Vector2f getPosition() const;
};