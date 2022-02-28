#pragma once
#include "Ball.h"

void AirResistanceTest(Ball& ball)
{
	float airDensity = 1;
	float crossSection = 1;
	float coefficient = 0.9;
	float speedSquared = ball.getSpeed()* ball.getSpeed();

	float airResistance = 0.5 * speedSquared * airDensity * coefficient * crossSection;
	sf::Vector2f unitVector = ball.getVelocity() / ball.getSpeed();

	sf::Vector2f airVector = -unitVector * airResistance;
	sf::Vector2f gravityVector(0, 0);
	gravityVector.y = -1 * 9.82;

	sf::Vector2f newVelocity = ball.getVelocity() - (airVector + gravityVector);
}