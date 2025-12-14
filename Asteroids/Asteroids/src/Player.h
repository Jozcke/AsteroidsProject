#pragma once
#include "Livingentity.h"
#include <SFML/Graphics.hpp>

class Player : public Livingentity
{
private:
    sf::ConvexShape ship;
    sf::Vector2f velocity;
    float rotationSpeed = 180.f;
    float acceleration = 300.f;
    float maxSpeed = 500.f;
    
    void rotateLeft(float dt);
    void rotateRight(float dt);
    void accelerate(float dt);
    void maxVelocity();

public:
    Player();
    void update(float dt, const sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    sf::Angle getRotation() const;
    void WrapAroundScreen(const sf::RenderWindow& window);
    void moveShip(float dt, sf::Vector2f velocity);
    sf::Vector2f shipForwardRotation();
    sf::Vector2f getPosition() const;
};

