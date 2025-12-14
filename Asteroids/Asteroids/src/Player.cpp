#include "Player.h"
#include <SFML/Graphics.hpp>
#include <math.h>

Player::Player() : Livingentity()
{
	ship.setPointCount(3);
	ship.setPoint(0, { 0.0f,-10.0f });
	ship.setPoint(1, { 10.0f,10.0f });
	ship.setPoint(2, { -10.0f,10.0f });
	ship.setFillColor(sf::Color::White);
	speed = 0.f;
	
	//compute geometric center
	sf::Vector2f centroid(0.f, 0.f);
	for (size_t i = 0; i < ship.getPointCount(); ++i)
		centroid += ship.getPoint(i);
	centroid /= static_cast<float>(ship.getPointCount());

	ship.setOrigin(centroid); // origin = geometric center
	
	ship.setPosition({ 400.f, 300.f });
	isAlive = true;
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
	
	moveShip(dt, velocity);
	maxVelocity();
	WrapAroundScreen(window);
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

void Player::moveShip(float dt, sf::Vector2f velocity)
{
	this->ship.move(dt * velocity);
}

sf::Vector2f Player::shipForwardRotation()
{
	//get ship front direction
	float rad = this->ship.getRotation().asRadians();
	return {std::sin(rad), -std::cos(rad)};
	
}
sf::Vector2f Player::getPosition() const
{
	return this->ship.getPosition();
}

void Player::accelerate(float dt)
{
	velocity += shipForwardRotation() * acceleration * dt;
}

void Player::WrapAroundScreen(const sf::RenderWindow& window)
{
	sf::Vector2f pos = ship.getPosition();
	sf::Vector2u size = window.getSize();

	if (pos.x < 0.f)
		pos.x = static_cast<float>(size.x);
	else if (pos.x > size.x)
		pos.x = 0.f;

	if (pos.y < 0.f)
		pos.y = static_cast<float>(size.y);
	else if (pos.y > size.y)
		pos.y = 0.f;

	ship.setPosition(pos);
}

void Player::maxVelocity()
{
	float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	if (speed > maxSpeed)
	velocity = (velocity / speed) * maxSpeed;
}