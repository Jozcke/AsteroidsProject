
#include "SFML/Graphics.hpp"
#include "Bullet.h"
#include "Player.h"

Bullet::Bullet(const sf::Vector2f& startPosition, const sf::Vector2f& direction) : Entity()
{
	shapeBullet.setRadius(2);
	shapeBullet.setFillColor(sf::Color::White);
	shapeBullet.setOrigin({ 2.f,2.f });
	
	setPosition(startPosition);
	velocity = direction * BULLETSPEED;
	setAlive(true);
	
	shapeBullet.setPosition(getPosition());
}

Bullet::~Bullet()
{
}

void Bullet::update(float dt, const sf::RenderWindow& window)
{
	
	setPosition(getPosition() + velocity * dt);  //<-- mathematical update of position.
	
	shapeBullet.setPosition(getPosition()); //<--- render logic for SFML.

	sf::Vector2u windowSize = window.getSize();
	const float OutOfView = 100.f;
	
	if (getPosition().x < -OutOfView || getPosition().x > windowSize.x + OutOfView ||
		getPosition().y < -OutOfView || getPosition().y > windowSize.y + OutOfView)
	{
		this->setAlive(false);  // mark for removal
	}
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(this->shapeBullet);
}

float Bullet::getRadius() const
{
	return this->shapeBullet.getRadius();
}