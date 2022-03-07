#pragma once
#include"Ball.h"

void InitializeCollisionTest(Ball& ball1, Ball& ball2)
{
	ball1.setPosition(100.0f, 210.0f);
	ball2.setPosition(300.0f, 200.0f);

	ball1.setVelocity(sf::Vector2f(2.0f, 0.0f));
	ball2.setVelocity(sf::Vector2f(-2.0f, 0.0f));
}

void CollisionTest(Ball &ball1, Ball &ball2, bool &collisionOnce)
{
	//ball1.collideWith(ball2);
	float massball1 = 100.0f;//check if kg,
	float massball2 = 50.0f;
	int ballvelocity[2];

	sf::Vector2f VelocityAfterCollision;
	float massnegative, massPositive;

	if (ball1.collideWith(ball2) && !collisionOnce)
	{
		collisionOnce == true;
		//ball1 velocity after collision calculation
		massnegative = massball1 - massball2;
		massPositive = massball1 + massball2;
		float massValue = massnegative / massPositive;
		sf::Vector2f v1Before, v2Before;
		v1Before.x = massValue * ball1.getVelocity().x;
		v1Before.y = massValue * ball1.getVelocity().y;

		float secondValue = (2 * massball2) / (massball1 + massball2);
		v2Before.x = secondValue * ball2.getVelocity().x;
		v2Before.y = secondValue * ball2.getVelocity().y;

		sf::Vector2f ball1FinalVelocity = v1Before + v2Before;

		//massnegative = (massnegative*ball1.getVelocity().x)

		//ball1 velocity after collision calculation
		float firstValueSecondBall = (2 * massball1) / massPositive;
		sf::Vector2f tempball1, tempball2;
		tempball1.x = firstValueSecondBall * ball1.getVelocity().x;
		tempball1.y = firstValueSecondBall * ball1.getVelocity().y;

		float secondValueSecondBall = (massball2 - massball1) / massPositive;
		tempball2.x = secondValueSecondBall * ball2.getVelocity().x;
		tempball2.y = secondValueSecondBall * ball2.getVelocity().y;
		sf::Vector2f ball2FinalVelocity = tempball1 + tempball2;

		//setting final velocity
		ball1.setVelocity(ball1FinalVelocity);
		ball2.setVelocity(ball2FinalVelocity);
	}
	ball1.move();
	ball2.move();
}