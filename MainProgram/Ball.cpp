#include "Ball.h"

Ball::Ball(float windowWidth, float windowHeight, sf::Vector2f speed, std::string texture, int radius)
	:GameEntity(windowWidth, windowHeight, texture, speed, radius),
	speed(speed)
{
}

Ball::~Ball()
{
}

void Ball::move()
{
	this->moveSprite();
}
