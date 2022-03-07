#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "AirResistance.h"
#include "CollisionTest.h"
#include<iostream>

#ifdef _DEBUG
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#else
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-graphics.lib")
#endif

const int WIDTH = 900;
const int HEIGHT = 600;
const int CAP = 50;

void initiateText(sf::Font& font, sf::Text& text);

int main()
{
	//1 Pixel is 1 cm
	float fps = 60;
	float deltaTime = 1.f / fps;

	bool once1 = true;
	bool once2 = true;

	std::srand((unsigned)time(0));
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Fysik projekt");

	sf::Clock clock;
	sf::Time elapsedTimeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(deltaTime);
	sf::Time timePlayed = sf::Time::Zero;

	sf::Text text;
	sf::Font font;
	initiateText(font, text);

	//Ball test(WIDTH,HEIGHT,sf::Vector2f(4.0f,12.0f), "Ball", 15);

	Ball collisionBall1(WIDTH, HEIGHT, sf::Vector2f(10.0f, 0.0f), "Ball");
	Ball collisionBall2(WIDTH, HEIGHT, sf::Vector2f(100.0f, 0.0f), "Ball");
	InitializeCollisionTest(collisionBall1, collisionBall2);

	while (window.isOpen())
	{
		
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
			}
		
			timePlayed += clock.getElapsedTime();
			elapsedTimeSinceLastUpdate += clock.restart();
			while (elapsedTimeSinceLastUpdate > timePerFrame)
			{
				CollisionTest(collisionBall1, collisionBall2);


				elapsedTimeSinceLastUpdate -= timePerFrame;
				text.setString("Time: " + std::to_string(timePlayed.asSeconds()));
				//test.move();
				//AirResistanceTest(test, deltaTime, once1, once2);
				//std::cout << "Speed: " << test.getSpeed() << std::endl; 
			}
		

		window.clear();

		window.draw(collisionBall1);
		window.draw(collisionBall2);

		window.draw(text);
		//window.draw(test);
		window.display();
	}


	return 0;
}

void initiateText(sf::Font& font, sf::Text& text)
{
	font.loadFromFile("C:/Windows/fonts/arial.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Green);
	text.setPosition(500.0f, 100.0f);
}
