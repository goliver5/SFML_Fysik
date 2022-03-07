#pragma once
#include "Ball.h"
#include <iostream>

void AirResistanceTest(Ball& ball, float deltaTime, bool &once1, bool &once2)
{
	//Variables that are useful

	//Densities
	float airDensity = 1.225;		//Density of air
	float density = 1.000f * 1000*0.02f;	//Density of object

	//Reduce the text amount and improves performance of the program
	float ballRadius = ball.getRadius();
	float speedSquared = ball.getSpeed() * ball.getSpeed();

	const int PI = 3.141529;		//Pi or close enough
	float coefficient = 0.5;		//How much the drag affects the object depends on its shape, and we found that our sphere roughly has this coefficient
	double crossSection = ballRadius * ballRadius * PI;

	float mass = density * (4.f / 3.f * PI * ballRadius * ballRadius * ballRadius); //We calculate the mass by: m = pV (p = density, V = volume)
	
	//Now it is time for the math
	//Air resistance (or drag)
	float airResistanceConstant = 0.5 * airDensity * coefficient * crossSection;		//The constant part of the drag force (none of these values should change during runtime)
	float dragForce = speedSquared * airResistanceConstant;								//Gives the force of the drag
	sf::Vector2f unitVector = ball.getVelocity() / ball.getSpeed();						//Normalized vector
	sf::Vector2f airVector = (-1.f) * unitVector * dragForce;							//-1 because it is opposite direction to the velocity

	//Gravity
	sf::Vector2f gravityVector(0, 0);		 
	gravityVector.y = mass * (-1) * 9.82;	//Force is negative since we view falling as minus in speed

	//Now we combine the two acting forces
	sf::Vector2f actingForces = gravityVector - coefficient * speedSquared * unitVector;
	//sf::Vector2f newVelocity2 = sf::Vector2f(0, mass * -(9.82)) + airVector;

	//F = ma
	//F = actingForces
	//m = mass
	//a = dV/dT


	sf::Vector2f newAcceleration = actingForces / (float)(mass);
	sf::Vector2f newVelocity = ball.getVelocity() + (newAcceleration * deltaTime);
	if (newVelocity.y <= 0.0f && once1)
	{
		
		std::cout << "Ball reached highest point at X = " << (float)ball.getBounds().left / 100 + (float)(ball.getBounds().width / 2) / 100 << "m" << std::endl;
		once1 = false;
	}

	if (ball.getBounds().top >= ball.getWindowHeight() - ball.getBounds().height && once2)
	{
		std::cout << "Ball reached bottom at X = " << (float)ball.getBounds().left / 100 + (float)(ball.getBounds().width / 2) / 100 << "m" << std::endl;
		once2 = false;
	}
	//F = ma
	//a = F/m

	//std::cout << "X pos in m: " << (float)ball.getBounds().left/100 + (float)(ball.getBounds().width/2)/100 << std::endl;

	//float airResistance = 0.25 * speedSquared * airDensity * coefficient * crossSection;
	ball.setVelocity(newVelocity);
}