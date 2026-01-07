#include "Player.h"
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Bullet.h"

Player::Player() : Livingentity()
{
	ship.setPointCount(3);
	ship.setPoint(0, { 0.0f,-10.0f });
	ship.setPoint(1, { 10.0f,10.0f });
	ship.setPoint(2, { -10.0f,10.0f });
	ship.setFillColor(sf::Color::White);
	
	setSpeed(0.f);
	setHealth(INITHEALTH);
	setAlive(true);
	
	//compute geometric center
	sf::Vector2f centroid(0.f, 0.f);
	for (size_t i = 0; i < ship.getPointCount(); ++i)
		centroid += ship.getPoint(i);
	centroid /= static_cast<float>(ship.getPointCount());

	ship.setOrigin(centroid); // origin = geometric center
	this->radius = playerRadius();
	
	ship.setPosition({ 400.f, 300.f });
	setPosition(ship.getPosition());
	
}

void Player::update(float dt, const sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		rotateLeft(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		rotateRight(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		accelerate(dt);
	}

	moveShip(dt);
	maxVelocity();
	Entity::wrapAroundScreen(window);
	ship.setPosition(getPosition());
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(this->ship);
}

sf::Angle Player::getRotation() const
{
	return this->ship.getRotation();
}

//MOVEMENT
void Player::rotateLeft(float dt)
{
	this->ship.rotate(sf::degrees(-rotationSpeed * dt));
}

void Player::rotateRight(float dt)
{
	this->ship.rotate(sf::degrees(rotationSpeed * dt));
}

void Player::moveShip(float dt)
{
	this->move(dt);
}

bool Player::Shoot() const
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
}
//END MOVEMENT


sf::Vector2f Player::shipForwardRotation()
{
	//get ship front direction
	float rad = this->ship.getRotation().asRadians();
	
	return {std::sin(rad), -std::cos(rad)};
	
}

float Player::getRadius() const
{
	return this->radius;
}

int Player::getHealth() const
{
	return this->Livingentity::getHealth();
}

void Player::takeDamage(int damage)
{;
	setHealth(getHealth() - damage);
}

void Player::accelerate(float dt)
{
	setVelocity(getVelocity() + shipForwardRotation() * acceleration * dt);
}

void Player::maxVelocity()
{
	sf::Vector2f velocity = getVelocity();
	
	float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	
	if (speed > maxSpeed)
		setVelocity((velocity / speed) * maxSpeed);

}

float Player::playerRadius()
{
	float maxDistance = 0.f;

	for (size_t i = 0; i < ship.getPointCount(); i++)
	{
		sf::Vector2f point = ship.getPoint(i);
		float distance = std::sqrt(point.x * point.x + point.y * point.y);
		maxDistance = std::max(maxDistance, distance);
	}
	
	return maxDistance * 0.75f;
}

void Player::reset(const sf::Vector2f& spawnPosition)
{
	setHealth(INITHEALTH);
	setAlive(true);
	setPosition(spawnPosition);
	setVelocity({ 0.f, 0.f });
	ship.setPosition(getPosition());
	ship.setRotation(sf::degrees(0.f));
}