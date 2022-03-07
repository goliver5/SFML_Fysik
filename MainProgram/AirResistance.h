#pragma once
#include "Ball.h"
#include <iostream>

void AirResistanceTest(Ball& ball, float deltaTime, bool &once1, bool &once2)
{
	//Densities
	float airDensity = 1.225;			//Density of air
	float mass = 1;						//Density of object

	//Reduce the text amount and improves performance of the program
	float ballRadius = ball.getRadius();
	float speedSquared = ball.getSpeed() * ball.getSpeed();
	float timeConstant = deltaTime * ((1.f / 60.f) / deltaTime);	//Our deltaTime, has the other part just to keep the same basis as the start

	const int PI = 3.141529;		//Pi or close enough
	float coefficient = 0.4;		//How much the drag affects the object depends on its shape, and we found that our sphere roughly has this coefficient
	double crossSection = ballRadius * ballRadius * PI;

	//float mass = density * (4.f / 3.f * PI * ballRadius * ballRadius * ballRadius); //We calculate the mass by: m = pV (p = density, V = volume)
	
	//Air resistance (or drag)
	float airResistanceConstant = 0.5 * airDensity * coefficient * crossSection;	//The constant part of the drag force (none of these values should change during runtime)
	float dragForce = speedSquared * airResistanceConstant;							//Gives the force of the drag
	sf::Vector2f unitVector = ball.getVelocity() / ball.getSpeed();					//Normalized vector
	sf::Vector2f airVector = (-1.f) * unitVector * dragForce;						//-1 because it is opposite direction to the velocity

	//Gravity
	sf::Vector2f gravityVector(0, 0);		 
	gravityVector.y = mass * (-1) * 9.82;	//Force is negative since we view falling as minus in speed

	//Now we combine the two acting forces
	sf::Vector2f actingForces = gravityVector + airVector;


	sf::Vector2f newVelocity = ball.getVelocity();				//We will now add the forces to this and get the new velocity

	//F = ma gives us actingForces = m * a  <==>  a = actingForces/m
	newVelocity.y += actingForces.y * timeConstant / mass;		//We multiply it by timeConstant since that is our deltaTime
	newVelocity.x += actingForces.x * timeConstant / mass;

	if (newVelocity.y <= 0.0f && once1) //When the ball has reached it is highest point our program writes in the console
	{
		
		std::cout << "Ball reached highest point at X = " << (float)ball.getBounds().left / 100 + (float)(ball.getBounds().width / 2) / 100 << "m" << std::endl;
		once1 = false;
	}

	if (ball.getBounds().top >= ball.getWindowHeight() - ball.getBounds().height && once2) //When the ball reaches the ground (same Y level as when we started)
	{
		std::cout << "Ball reached bottom at X = " << (float)ball.getBounds().left / 100 + (float)(ball.getBounds().width / 2) / 100 << "m" << std::endl;
		once2 = false;
	}

	ball.setVelocity(newVelocity);
}