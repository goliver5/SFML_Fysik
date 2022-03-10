#pragma once
#include "Ball.h"
#include <iostream>

void InitializeAirResistanceTest(Ball& ball, bool& once1, bool& once2)
{
	ball.setPosition(0.f, ball.getWindowHeight() - ball.getBounds().height);
	ball.setVelocity(sf::Vector2f(4.0f, -12.0f));
	once1 = true;
	once2 = true;
}

void removeAirResistanceTest(Ball& ball)
{
	ball.setPosition(1000.0f, 1000.0f);
	ball.setVelocity(sf::Vector2f(0.0f, 0.0f));
}

void AirResistanceTest(Ball& ball, float deltaTime, bool &once1, bool &once2, bool air)
{
	ball.move();
	float airDensity = 1.225;			//Density of air
	float mass = ball.getWeight();

	//Reduce the text amount
	float ballRadius = ball.getRadius();
	float speedSquared = ball.getSpeed() * ball.getSpeed();
	float timeConstant = deltaTime * ((1.f / 60.f) / deltaTime);	//Our deltaTime multiplier

	const int PI = 3.141529;
	float coefficient = 0.29;		//How much the drag affects the object depends on its shape, and we found that our sphere roughly has this coefficient
	double crossSection = ballRadius * ballRadius * PI;
	
	//Air resistance (or drag)
	float airResistanceConstant = 0.5 * airDensity * coefficient * crossSection;	//The constant part of the drag force (none of these values should change during runtime)
	float dragForce = speedSquared * airResistanceConstant;							//Gives the force of the drag
	sf::Vector2f unitVector = ball.getVelocity() / ball.getSpeed();					//Normalized vector
	sf::Vector2f airVector = (-1.f) * unitVector * dragForce;						//-1 because it is opposite direction to the velocity
	airVector.y = airVector.y * (-1.f);												//Explained in row 51

	if (!air) airVector = sf::Vector2f(0.f, 0.f);

	//Gravity
	sf::Vector2f gravityVector(0, 0);		 
	gravityVector.y = mass * (-1) * 9.82;	//Force is negative since we view falling as minus in speed

	//Now we combine the two acting forces
	sf::Vector2f actingForces = gravityVector + airVector;

	sf::Vector2f newVelocity = ball.getVelocity();				//We will now add the forces to this and get the new velocity

	//F = ma gives us actingForces = m * a  <==>  a = actingForces/m
	newVelocity.y -= actingForces.y * timeConstant / mass;				//Since -y in this program means up(bottom of screen is higher y - value than top of screen)
	newVelocity.x += actingForces.x * timeConstant / mass;
	//We multiply by timeConstant since that is our deltaTime

	if (newVelocity.y >= 0.0f && once1) //When the ball has reached it is highest point our program writes in the console
	{
		
		std::cout << "Ball reached highest point at X = " << (float)ball.getBounds().left / 100 + (float)(ball.getBounds().width / 2) / 100 << "m" << std::endl;
		once1 = false;
	}

	if (ball.getBounds().top >= ball.getWindowHeight() - ball.getBounds().height && once2) //When the ball reaches the ground (same Y level as when we started)
	{
		std::cout << "Ball reached bottom at X = " << (float)ball.getBounds().left / 100 + (float)(ball.getBounds().width / 2) / 100 << "m" << std::endl;
		once2 = false;
		removeAirResistanceTest(ball);
	}

	ball.setVelocity(newVelocity);
}

