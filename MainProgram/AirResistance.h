#pragma once
#include "Ball.h"
#include <iostream>

void AirResistanceTest(Ball& ball, float deltaTime)
{
	const int PI = 3.141529;
	float density = 7.874f * 1000;
	float ballRadius = ball.getRadius();
	float mass = density * 4.f / 3.f * PI * ballRadius * ballRadius * ballRadius;
	int gameBalancing = 1 / 100;
	float airDensity = 1.225; //kg/m3
	double crossSection = ballRadius * ballRadius * PI;
	float coefficient = 0.5;
	float speedSquared = ball.getSpeed()* ball.getSpeed();

	std::cout << "Radius in m: " << ball.getRadius() << std::endl;
	float airResistance = -0.5 * speedSquared * airDensity * coefficient * crossSection;
	//float airResistance = 0.25 * speedSquared * airDensity * coefficient * crossSection;
	sf::Vector2f unitVector = ball.getVelocity() / ball.getSpeed();

	sf::Vector2f airVector = unitVector * airResistance;
	sf::Vector2f gravityVector(0, 0);
	gravityVector.y = mass * (-1) * 9.82;

	sf::Vector2f newVelocity2 = sf::Vector2f(0, mass * -(9.82)) - coefficient * speedSquared * unitVector;

	

	sf::Vector2f newAcceleration = newVelocity2 / (float)(mass);
	sf::Vector2f newVelocity = ball.getVelocity() + (newAcceleration * deltaTime);
	//F = ma
	//a = F/m
	ball.setVelocity(newVelocity);
}