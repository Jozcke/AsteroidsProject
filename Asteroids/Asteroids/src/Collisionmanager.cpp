#include "Collisionmanager.h"
#include "SFML/Graphics.hpp"


bool Collisionmanager::circleCollision(const sf::Vector2f& aPos, float aRadius, const sf::Vector2f& bPos, float bRadius)
{

	sf::Vector2f deltaPos = aPos - bPos;


	float sqrDistance = (deltaPos.x * deltaPos.x) + (deltaPos.y * deltaPos.y); 
	float sumRadius = aRadius + bRadius;

	return sqrDistance <= sumRadius * sumRadius;  //compare suqre distance to the square of sum radius instead of sqr-root -> faster computing. 
}
