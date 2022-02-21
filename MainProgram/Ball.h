#pragma once
#include "GameEntity.h"

class Ball : public GameEntity
{
private:
	sf::Vector2f speed;

public:
	Ball(float windowWidth, float windowHeight, sf::Vector2f speed, std::string texture);
	~Ball();

	// Inherited via GameEntity
	virtual void move() override;
};