#pragma once
#include "Livingentity.h"
#include <SFML/Graphics.hpp>

class Player : public Livingentity
{
private:
    sf::ConvexShape ship;
    float rotationSpeed = 180.f;
    float acceleration = 300.f;
    float maxSpeed = 500.f;
    float radius;
    int score;
    const int INITHEALTH = 3;
    
    void rotateLeft(float dt);
    void rotateRight(float dt);
    void accelerate(float dt);
    void maxVelocity();

public:
    Player();
    void update(float dt, const sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    void moveShip(float dt);
    bool Shoot() const;
    void reset(const sf::Vector2f& spawnPosition);
    
    sf::Vector2f shipForwardRotation();
    sf::Angle getRotation() const;
    float getRadius() const;
    float playerRadius();
    int getHealth() const;
    void takeDamage(int damage);
};

