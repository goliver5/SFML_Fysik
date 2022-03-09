#pragma once
#include "GameEntity.h"

class Ball : public GameEntity
{
private:
	int weight;
public:
	Ball(float windowWidth, float windowHeight, sf::Vector2f speed, std::string texture, int radius = 15, int color = 0, float weight = 50);
	~Ball();

	float getWeight();

	// Inherited via GameEntity
	virtual void move() override;
};