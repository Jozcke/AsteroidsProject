
#include "SFML/Graphics.hpp"
#include "Bullet.h"
#include "Player.h"

Bullet::Bullet(const sf::Vector2f& startPosition, const sf::Vector2f& direction) : Entity()
{
	shapeBullet.setRadius(2);
	shapeBullet.setFillColor(sf::Color::White);
	shapeBullet.setOrigin({ 2.f,2.f });
	
	Entity::position = startPosition;
	velocity = direction * BULLETSPEED;

	alive = true;
}

Bullet::~Bullet()
{
}

void Bullet::update(float dt, const sf::RenderWindow& window)
{
	
	position += velocity * dt;  //<-- mathematical update of position.
	
	shapeBullet.setPosition(position); //<--- render logic for SFML.

	sf::Vector2u windowSize = window.getSize();
	const float OutOfView = 100.f;
	if (position.x < -OutOfView || position.x > windowSize.x + OutOfView ||
		position.y < -OutOfView || position.y > windowSize.y + OutOfView)
	{
		alive = false;  // mark for removal
	}
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(this->shapeBullet);
}

bool Bullet::getAlive() const
{
	return this->alive;
}