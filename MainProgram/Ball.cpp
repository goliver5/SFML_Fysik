#include "Ball.h"

Ball::Ball(float windowWidth, float windowHeight, sf::Vector2f speed, std::string texture, int radius, int color, float weight)
	:GameEntity(windowWidth, windowHeight, texture, speed, radius, color)
{
	this->weight = weight;
}

Ball::~Ball()
{
}

float Ball::getWeight()
{
	return this->weight;
}

void Ball::move()
{
	this->moveSprite();
}
