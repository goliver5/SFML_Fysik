#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "AirResistance.h"
#include "CollisionTest.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>

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
void writeToFile(std::string filename, std::vector<sf::Vector2f>& ball, std::vector<sf::Vector2f>& position);
void saveValues(std::vector<sf::Vector2f>& values, std::vector<sf::Vector2f>& position, Ball& collisionBall1, Ball& collisionBall2, Ball& airBall, int whichTestToSave);

int main()
{

	srand(time(NULL));
	//1 Pixel is 1 cm
	float fps = 60;
	float deltaTime = 1.f / fps;
	
	int counter = 0;
	int saveAmount = 10;
	int framesBetweenSaves = fps / saveAmount;

	bool once1 = true;
	bool once2 = true;
	bool air = true;
	int whichTest = 0;


	//ball values storage
	std::vector<sf::Vector2f> values;
	std::vector<sf::Vector2f> position;
	std::vector<sf::Vector2f> markerPos;
	std::vector<Ball> collisionBalls;
	std::vector<sf::Vector2i> timer;

	std::srand((unsigned)time(0));
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Fysik projekt");

	sf::CircleShape marker(3);
	marker.setFillColor(sf::Color::Red);

	sf::Clock clock;
	sf::Time elapsedTimeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(deltaTime);
	sf::Time timePlayed = sf::Time::Zero;

	sf::Text text;
	sf::Font font;
	initiateText(font, text);

	Ball airTestBall(WIDTH,HEIGHT,sf::Vector2f(4.0f,12.0f), "Ball", 15, 0, 1);

	Ball collisionBall1(WIDTH, HEIGHT, sf::Vector2f(10.0f, 0.0f), "Ball");
	Ball collisionBall2(WIDTH, HEIGHT, sf::Vector2f(10.0f, 0.0f), "Ball");


	for (int i = 0; i < 8; i++)
	{
		collisionBalls.push_back(Ball(WIDTH, HEIGHT, sf::Vector2f(1, -2.0f), "Ball"));
		collisionBalls[i].setPosition(i * 100, i * 100);
		timer.push_back(sf::Vector2i(0, 11));
	}

	window.setKeyRepeatEnabled(false);

	while (window.isOpen())
	{
		
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Space)
					{
						for (int i = 0; i < collisionBalls.size(); i++)
						{
							values.push_back(collisionBalls[i].getVelocity());
							position.push_back(collisionBalls[i].getPosition());
							std::cout << "Position: (" << collisionBalls[i].getPosition().x << ", " << collisionBalls[i].getPosition().y << ") " << " velocity: (" << collisionBalls[i].getVelocity().x << ", " << collisionBalls[i].getVelocity().y << ")" << std::endl;
						}
						
					}
					if (event.key.code == sf::Keyboard::S)
					{
						writeToFile("test.txt", values, position);
					}
					if (event.key.code == sf::Keyboard::Num1)
					{
						InitializeCollisionTest(collisionBall1, collisionBall2);
						removeAirResistanceTest(airTestBall);
						markerPos.clear();
						whichTest = 1;
					}
					if (event.key.code == sf::Keyboard::Num2)
					{
						removeCollisionTest(collisionBall1, collisionBall2);
						InitializeAirResistanceTest(airTestBall, once1, once2);
						whichTest = 2;
						markerPos.clear();
						air = true;
					}
					if (event.key.code == sf::Keyboard::Num3)
					{
						//removeCollisionTest(collisionBalls[0], collisionBalls[1]);
						InitializeMultipleBallsCollisionTest(collisionBalls);
						whichTest = 3;
						markerPos.clear();
					}
					if (event.key.code == sf::Keyboard::Num4)
					{
						removeCollisionTest(collisionBall1, collisionBall2);
						InitializeAirResistanceTest(airTestBall, once1, once2);
						whichTest = 4;
						air = false;
					}
					if (event.key.code == sf::Keyboard::Num5)
					{
						InitializeCollisionTest2(collisionBall1, collisionBall2);
						removeAirResistanceTest(airTestBall);
						markerPos.clear();
						whichTest = 5;
					}
				}
				
			}
		
			timePlayed += clock.getElapsedTime();
			elapsedTimeSinceLastUpdate += clock.restart();
			while (elapsedTimeSinceLastUpdate > timePerFrame)
			{
				counter++;
				if (counter == framesBetweenSaves)
				{
					saveValues(values, position, collisionBall1, collisionBall2, airTestBall, whichTest);
					counter = 0;
					switch (whichTest)
					{
					default:
						break;
					case 1:
						markerPos.push_back(collisionBall1.getPosition() - sf::Vector2f(2, 2));
						markerPos.push_back(collisionBall2.getPosition() - sf::Vector2f(2, 2));
						break;
					case 2:
						markerPos.push_back(airTestBall.getPosition() - sf::Vector2f(2, 2));
						break;
					case 4:
						markerPos.push_back(airTestBall.getPosition() - sf::Vector2f(2, 2));
						break;
					}
				}
				switch (whichTest)
				{
				default: 
					break;
				case 1:
					if (collisionBall1.collideWith(collisionBall2))
					{
						CollisionTest(collisionBall1, collisionBall2, 1);
					}
					collisionBall1.move();
					collisionBall2.move();
					bounceOfWall(collisionBall1);
					bounceOfWall(collisionBall2);
					break;
				case 3:
					for (int i = 0; i < collisionBalls.size(); i++)
					{
						for (int b = i+1; b < collisionBalls.size(); b++)
						{
							if (collisionBalls[i].collideWith(collisionBalls[b]))
							{
								if (timer[i].x == 0 && timer[b].x == 0)
								{
									CollisionTest(collisionBalls[i], collisionBalls[b], 1);
									timer[i].x++;
									timer[b].x++;
								}
							}
						}
					}
					for (int i = 0; i < collisionBalls.size(); i++)
					{
						bounceOfWall(collisionBalls[i]);
						collisionBalls[i].move();
						if (timer[i].x != 0) timer[i].x = (timer[i].x + 1) % timer[i].y;
					}
					
					break;
				case 2:
					AirResistanceTest(airTestBall, deltaTime, once1, once2, air);
					break;
				case 4:
					AirResistanceTest(airTestBall, deltaTime, once1, once2, air);
					break;
				case 5:
					if (collisionBall1.collideWith(collisionBall2))
					{
						CollisionTest(collisionBall1, collisionBall2, 1);
					}
					collisionBall1.move();
					collisionBall2.move();
					break;
				}
				elapsedTimeSinceLastUpdate -= timePerFrame;
				text.setString("Time: " + std::to_string(timePlayed.asSeconds()));
			}


		window.clear();
		if (whichTest != 3)
		{
			for (int i = 0; i < markerPos.size(); i++)
			{
				marker.setPosition(markerPos[i]);
				window.draw(marker);
			}
		}
		
	
		switch (whichTest)
		{
		default:
			break;
		case 1:
			window.draw(collisionBall1);
			window.draw(collisionBall2);
			break;
		case 2:
			window.draw(airTestBall);
			break;
		case 3:
			for (int i = 0; i < collisionBalls.size(); i++)
			{
				window.draw(collisionBalls[i]);
			}
		case 4:
			window.draw(airTestBall);
			break;
		case 5:
			window.draw(collisionBall1);
			window.draw(collisionBall2);
			break;
		break;
		}
		

		window.draw(text);
		window.display();
	}


	return 0;
}

void initiateText(sf::Font& font, sf::Text& text)
{
	font.loadFromFile("C:/Windows/fonts/arial.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Green);
	text.setPosition(WIDTH-300, 0.0f);
}

void writeToFile(std::string filename, std::vector<sf::Vector2f>& ball, std::vector<sf::Vector2f>& position)
{
	std::ofstream file{ filename };
	std::ofstream out;
	//out.open(filename);
	out.open(filename);
	if (out.is_open())
	{
		for (int i = 0; i < ball.size(); i++)
		{
			out << "Position: (" << position[i].x << ", " << position[i].y << ") " << " velocity: (" << ball[i].x << ", " << ball[i].y << ")" << std::endl;
		}
	}
	else
	{
		std::cout << "\nCouldnt write to this file\n";
	}
}

void saveValues(std::vector<sf::Vector2f>& values, std::vector<sf::Vector2f>& position, Ball & collisionBall1, Ball &collisionBall2, Ball &airBall, int whichTestToSave)
{
	switch (whichTestToSave)
	{
	case 1:
		values.push_back(collisionBall1.getVelocity());
		position.push_back(collisionBall1.getPosition());
		values.push_back(collisionBall2.getVelocity());
		position.push_back(collisionBall2.getPosition());
		break;
	case 2:
		values.push_back(airBall.getVelocity());
		position.push_back(airBall.getPosition());
	default:
		break;
	}
	
}
