#pragma once
#include "GameEntity.h"

class Ball : public GameEntity
{
private:

public:
	Ball(float windowWidth, float windowHeight, sf::Vector2f speed, std::string texture, int radius = 15);
	~Ball();

	// Inherited via GameEntity
	virtual void move() override;
};