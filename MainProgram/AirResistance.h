#pragma once
#include "Ball.h"
#include <iostream>

void AirResistanceTest(Ball& ball)
{
	const int PI = 3.141529;
	int gameBalancing = 1 / 100;
	float airDensity = 1.225; //kg/m3
	double crossSection = ball.getRadius() * ball.getRadius() * PI;
	float coefficient = 0.5;
	float speedSquared = ball.getSpeed()* ball.getSpeed();

	std::cout << "Radius in m: " << ball.getRadius() << std::endl;
	float airResistance = -0.5 * speedSquared * airDensity * coefficient * crossSection;
	//float airResistance = 0.25 * speedSquared * airDensity * coefficient * crossSection;
	sf::Vector2f unitVector = ball.getVelocity() / ball.getSpeed();

	sf::Vector2f airVector = unitVector * airResistance;
	sf::Vector2f gravityVector(0, 0);
	gravityVector.y = -(7.874*4.f/3.f*PI* ball.getRadius() * ball.getRadius()* ball.getRadius()) * 9.82;

	sf::Vector2f newVelocity2 = sf::Vector2f(0, -(7.874 * 4.f / 3.f * PI * ball.getRadius() * ball.getRadius() * ball.getRadius()) * 9.82) - coefficient * speedSquared * unitVector;

	sf::Vector2f newVelocity = ball.getVelocity() + newVelocity2;
	//ball.setVelocity(newVelocity);
}