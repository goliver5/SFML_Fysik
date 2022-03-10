#pragma once
#include"Ball.h"

void InitializeCollisionTest(Ball& ball1, Ball& ball2)
{
	ball1.setPosition(425.0f, 320.0f);
	ball2.setPosition(400.0f, 200.0f);

	ball1.setVelocity(sf::Vector2f(0.f, -2.0f));
	ball2.setVelocity(sf::Vector2f(0.f, 2.0f));
}

void InitializeCollisionTest2(Ball& ball1, Ball& ball2)
{
	ball1.setPosition(500.0f, 310.0f);
	ball2.setPosition(300.0f, 300.0f);

	ball1.setVelocity(sf::Vector2f(-2.0f, 0.0f));
	ball2.setVelocity(sf::Vector2f(2.0f, 0.0f));
}

void InitializeMultipleBallsCollisionTest(std::vector<Ball> &balls)
{
	if (balls.size() == 8)
	{
		for (int i = 0; i < balls.size(); i++)
		{
			switch (i)
			{
			case 0:
				balls[i].setPosition(100,55);
				balls[i].setVelocity(sf::Vector2f(-2.f, 1.f));
				break;
			case 1:
				balls[i].setPosition(340, 255);
				balls[i].setVelocity(sf::Vector2f(2.f, 1.f));
				break;
			case 2:
				balls[i].setPosition(260, 455);
				balls[i].setVelocity(sf::Vector2f(-2.f, 2.f));
				break;
			case 3:
				balls[i].setPosition(115, 335);
				balls[i].setVelocity(sf::Vector2f(-1.f, -2.f));
				break;
			case 4:
				balls[i].setPosition(120, 235);
				balls[i].setVelocity(sf::Vector2f(-1.f, 1.f));
				break;
			case 5:
				balls[i].setPosition(420, 200);
				balls[i].setVelocity(sf::Vector2f(-2.f, -1.f));
				break;
			case 6:
				balls[i].setPosition(510, 255);
				balls[i].setVelocity(sf::Vector2f(2.f, -1.f));
				break;
			case 7:
				balls[i].setPosition(620, 315);
				balls[i].setVelocity(sf::Vector2f(-1.f, 1.f));
				break;
			default:
				break;
			}
		}
	}
}

void removeCollisionTest(Ball& ball1, Ball& ball2)
{
	ball1.setPosition(1000.0f, 1000.0f);
	ball1.setPosition(1000.0f, 1000.0f);

	ball1.setVelocity(sf::Vector2f(0.0f, 0.0f));
	ball2.setVelocity(sf::Vector2f(0.0f, 0.0f));
}

void bounceOfWall(Ball& ball)
{
	if (ball.getBounds().top <= 0)
	{
		ball.setPosition(ball.getBounds().left, 0);
		sf::Vector2f newVelocity = ball.getVelocity();
		newVelocity.y = -newVelocity.y;
		ball.setVelocity(newVelocity);
	}
	else if (ball.getBounds().top + ball.getBounds().height >= ball.getWindowHeight())
	{
		ball.setPosition(ball.getBounds().left, ball.getWindowHeight()- ball.getBounds().height);
		sf::Vector2f newVelocity = ball.getVelocity();
		newVelocity.y = -newVelocity.y;
		ball.setVelocity(newVelocity);
	}
	if (ball.getBounds().left <= 0)
	{
		ball.setPosition(0, ball.getBounds().top);
		sf::Vector2f newVelocity = ball.getVelocity();
		newVelocity.x = -newVelocity.x;
		ball.setVelocity(newVelocity);
	}
	else if (ball.getBounds().left + ball.getBounds().width >= ball.getWindowWidth())
	{
		ball.setPosition(ball.getWindowWidth() - ball.getBounds().width, ball.getBounds().top);
		sf::Vector2f newVelocity = ball.getVelocity();
		newVelocity.x = -newVelocity.x;
		ball.setVelocity(newVelocity);
	}
}

void inelasticCollision(Ball& ball1, Ball& ball2)
{

	float massball1 = ball1.getWeight();
	float massball2 = ball2.getWeight();

	sf::Vector2f VelocityAfterCollision;

	//test för rörelsemängd

	//vektor mellan bollarna
	sf::Vector2f vbb, vbb2;
	vbb = ball1.getPosition() - ball2.getPosition();//hastighet på VN
	vbb2 = ball2.getPosition() - ball1.getPosition();

	//hastighet projektion hastighet på vektorn mellan bollarna 
	//hastighet från boll 1
	//sf::Vector2f vN1  = (((ball1.getVelocity().x * vbb.x) + (ball1.getVelocity().y * vbb.y)) / ((vbb.x * vbb.x) + (vbb.y * vbb.y))) * vbb;
	//sf::Vector2f vN2 = (((ball2.getVelocity().x * -vbb.x) + (ball1.getVelocity().y * vbb.y)) / ((vbb.x * vbb.x) + (vbb.y * vbb.y))) * vbb;

	sf::Vector2f vN1 = (((ball1.getVelocity().x * vbb.x) + (ball1.getVelocity().y * vbb.y)) / ((vbb.x * vbb.x) + (vbb.y * vbb.y))) * vbb;
	sf::Vector2f vN2 = (((ball2.getVelocity().x * vbb2.x) + (ball2.getVelocity().y * vbb2.y)) / ((vbb2.x * vbb2.x) + (vbb2.y * vbb2.y))) * vbb2;
	//parallel med kollisionsplanet
	sf::Vector2f vP1 = ball1.getVelocity() - vN1;
	sf::Vector2f vP2 = ball2.getVelocity() - vN2;

	float e = 0.5; //om e like med noll så är den fullständigt oelastisk, för elastiska kollisioner är allt e = 1
	float masstemp = (massball1 - (massball2 * e));
	float masstempNegative = (massball2 - (e * massball1));
	float massPositive = massball1 + massball2;
	//for ball 1
	sf::Vector2f v1 = sf::Vector2f(vN1.x * masstemp, vN1.y * masstemp);
	sf::Vector2f v2 = sf::Vector2f(massball2 * vN2.x * (1 * e), massball2 * vN2.y * (1 * e));
	sf::Vector2f v3 = v1 + v2;
	sf::Vector2f finalVn1 = sf::Vector2f(v3.x / massPositive, v3.y / massPositive);

	//plussa på vn och vp
	ball1.setVelocity(finalVn1 + vP1);

	//för ball 2

	sf::Vector2f v4 = sf::Vector2f(vN1.x * massball1 * (1 + e), vN1.y * massball1 * (1 + e));
	sf::Vector2f v5 = sf::Vector2f(vN2.x * masstempNegative, vN2.y * masstempNegative);
	sf::Vector2f v6 = v4 + v5;
	sf::Vector2f finalvN2 = sf::Vector2f(v6.x / massPositive, v6.y / massPositive);

	ball2.setVelocity(finalvN2 + vP2);
}

void elasticCollision(Ball& ball1, Ball& ball2)
{
	//ball1.collideWith(ball2);
	//float massball1 = 50.0f;//check if kg,
	//float massball2 = 50.0f;
	float massball1 = ball1.getWeight();
	float massball2 = ball2.getWeight();

	sf::Vector2f VelocityAfterCollision;
	float massnegative, massPositive;

	//test för rörelsemängd

	//vektor mellan bollarna
	sf::Vector2f vbb, vbb2;
	vbb = ball1.getPosition() - ball2.getPosition();//hastighet på VN
	vbb2 = ball2.getPosition() - ball1.getPosition();

	//hastighet projektion hastighet på vektorn mellan bollarna 
	//hastighet från boll 1
	//sf::Vector2f vN1  = (((ball1.getVelocity().x * vbb.x) + (ball1.getVelocity().y * vbb.y)) / ((vbb.x * vbb.x) + (vbb.y * vbb.y))) * vbb;
	//sf::Vector2f vN2 = (((ball2.getVelocity().x * -vbb.x) + (ball1.getVelocity().y * vbb.y)) / ((vbb.x * vbb.x) + (vbb.y * vbb.y))) * vbb;

	sf::Vector2f vN1 = (((ball1.getVelocity().x * vbb.x) + (ball1.getVelocity().y * vbb.y)) / ((vbb.x * vbb.x) + (vbb.y * vbb.y))) * vbb;
	sf::Vector2f vN2 = (((ball2.getVelocity().x * vbb2.x) + (ball2.getVelocity().y * vbb2.y)) / ((vbb2.x * vbb2.x) + (vbb2.y * vbb2.y))) * vbb2;
	//parallel med kollisionsplanet
	sf::Vector2f vP1 = ball1.getVelocity() - vN1;
	sf::Vector2f vP2 = ball2.getVelocity() - vN2;

	//ball1 velocity after collision calculation
	massnegative = massball1 - massball2;
	massPositive = massball1 + massball2;
	float massValue = massnegative / massPositive;
	sf::Vector2f v1Before, v2Before;
	//v1Before.x = massValue * ball1.getVelocity().x;
	//v1Before.y = massValue * ball1.getVelocity().y;
	v1Before.x = massValue * vN1.x;
	v1Before.y = massValue * vN1.y;

	float secondValue = (2 * massball2) / (massball1 + massball2);
	/*v2Before.x = secondValue * ball2.getVelocity().x;
	v2Before.y = secondValue * ball2.getVelocity().y;*/
	v2Before.x = secondValue * vN2.x;
	v2Before.y = secondValue * vN2.y;

	sf::Vector2f ball1FinalVelocity = v1Before + v2Before;
	ball1FinalVelocity = ball1FinalVelocity + vP1;

	//massnegative = (massnegative*ball1.getVelocity().x)

	//ball1 velocity after collision calculation
	float firstValueSecondBall = (2 * massball1) / massPositive;
	sf::Vector2f tempball1, tempball2;
	tempball1.x = firstValueSecondBall * vN1.x;
	tempball1.y = firstValueSecondBall * vN1.y;

	float secondValueSecondBall = (massball2 - massball1) / massPositive;
	tempball2.x = secondValueSecondBall * vN2.x;
	tempball2.y = secondValueSecondBall * vN2.y;
	sf::Vector2f ball2FinalVelocity = tempball1 + tempball2;
	ball2FinalVelocity = ball2FinalVelocity + vP2;

	//setting final velocity
	ball1.setVelocity(ball1FinalVelocity);
	ball2.setVelocity(ball2FinalVelocity);
}

void CollisionTest(Ball &ball1, Ball &ball2, int temp)
{
	
	switch (temp)
	{
	default:
		break;
		elasticCollision(ball1, ball2);
	case 1:
		elasticCollision(ball1, ball2);
		break;
	case 2:
		inelasticCollision(ball1, ball2);
		break;
	}
	//elasticCollision(ball1, ball2);
	//inelasticCollision();

}