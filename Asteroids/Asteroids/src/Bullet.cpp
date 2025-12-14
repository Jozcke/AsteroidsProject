
#include "SFML/Graphics.hpp"
#include "Bullet.h"
#include "Player.h"

Bullet::Bullet(sf::Vector2f& startPosition, const sf::Vector2f& direction) : Entity()
{
	shapeBullet.setRadius(2);
	shapeBullet.setFillColor(sf::Color::White);
	shapeBullet.setOrigin({ 2.f,2.f });
	
	position = startPosition;
	velocity = direction * BULLETSPEED;

	isAlive = true;
}

Bullet::~Bullet()
{
}

void Bullet::update(float dt, const sf::RenderWindow& window)
{
	position += velocity * dt;  //<-- mathematical update of position.
	shapeBullet.setPosition(position); //<--- render logic for SFML.

	LifeTime -= dt;
	if (LifeTime <= 0.f)
	{
		isAlive = false;
	}
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(this->shapeBullet);
}

void Bullet::shoot(sf::Vector2f& position)
{

}