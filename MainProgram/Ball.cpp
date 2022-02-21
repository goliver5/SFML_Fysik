#include "Ball.h"

Ball::Ball(float windowWidth, float windowHeight, sf::Vector2f speed, std::string texture)
	:GameEntity(windowWidth, windowHeight, texture, speed),
	speed(speed)
{
}

Ball::~Ball()
{
}

void Ball::move()
{
	this->moveSprite(this->speed);
}
