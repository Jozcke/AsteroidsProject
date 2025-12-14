#pragma once
#include "Entity.h"
#include "Player.h"
#include "SFML/Graphics.hpp"



class Bullet : public Entity
{
private:
	sf::CircleShape shapeBullet;
	sf::Vector2f position;
	sf::Vector2f velocity;
	const float BULLETSPEED = 400.f;
	float LifeTime = 4.f;

public:
	Bullet(sf::Vector2f& startPosition, const sf::Vector2f& direction);
	~Bullet();
	void update(float dt, const sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window) override;
	void shoot(sf::Vector2f& position);

};