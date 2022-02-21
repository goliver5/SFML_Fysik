#include <SFML/Graphics.hpp>
#include"Fly.h"
#include"Tomato.h"
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

void drawFlies(Fly arr[], sf::RenderWindow &window);
void initiateFlies(Fly arr[]);
void moveFlies(Fly arr[]);
void spawnFlies(Fly arr[],int &nrOfFliesSpawned);
bool checkIfDespawn(Tomato &tomato, Fly arr[], int &nrOf, int &nrOffDespawn);
void initiateText(sf::Font& font, sf::Text& text);

int main()
{
	std::srand((unsigned)time(0));
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "DV1594 Muntlig tentamen 3");

	sf::Clock clock;
	sf::Time elapsedTimeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timePlayed = sf::Time::Zero;

	sf::Text text;
	sf::Font font;
	initiateText(font, text);


	int nrOfFliesSpawned = 5;
	int nrOffDespawn = 0;

	Tomato tomato(HEIGHT, WIDTH);

	Fly flies[CAP];
	initiateFlies(flies);

	spawnFlies(flies, nrOfFliesSpawned);

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
			if (tomato.getHealth() >= 1)
			{
			timePlayed += clock.getElapsedTime();
			elapsedTimeSinceLastUpdate += clock.restart();
			while (elapsedTimeSinceLastUpdate > timePerFrame)
			{

				elapsedTimeSinceLastUpdate -= timePerFrame;

				tomato.move();
				moveFlies(flies);
				if (checkIfDespawn(tomato, flies, nrOfFliesSpawned, nrOffDespawn))
				{
					spawnFlies(flies, nrOfFliesSpawned);
				}
				//text.setString(std::to_string(tomato.getHealth()));
				text.setString("Time: " + std::to_string(timePlayed.asSeconds()) + 
								"\nHealth: " + std::to_string(tomato.getHealth()));

			}
		}
		window.clear();

		if (tomato.getHealth() >= 1)
		{
			drawFlies(flies, window);
			window.draw(tomato);
		}
		else
		{
			text.setString("Time: " + std::to_string(timePlayed.asSeconds()) +
				"\nGame Over");
		}
		window.draw(text);

		window.display();
	}


	return 0;
}

void drawFlies(Fly arr[], sf::RenderWindow& window)
{
	for (int i = 0; i < CAP; i++)
	{
		window.draw(arr[i]);
	}
}

void initiateFlies(Fly arr[])
{
	for (int i = 0; i < CAP; i++)
	{
		arr[i].deSpawn();
		arr[i].setWindow(HEIGHT, WIDTH);
	}
}

void moveFlies(Fly arr[])
{
	for (int i = 0; i < CAP; i++)
	{
		arr[i].move();
	}
}

void spawnFlies(Fly arr[], int& nrOfFliesSpawned)
{
	for (int i = 0; i < nrOfFliesSpawned; i++)
	{
		arr[i].spawn();
	}
	//nrOfFliesSpawned += 5;
}

bool checkIfDespawn(Tomato &tomato, Fly arr[], int &nrOf, int &nrOffDespawn)
{

	bool allHaveDespawned = false;
	for (int i = 0; i < nrOf; i++)
	{
		if (arr[i].getXposition() + arr[i].getBounds().width < 0.0f)// om utanför fönstret
		{
			nrOffDespawn++;
			arr[i].deSpawn();
		}
		if (tomato.isHit(arr[i]))//kod för if hit
		{
			arr[i].deSpawn();
			nrOffDespawn++;
			tomato.decreaseHealth(arr[i]);
		}
		
	}
	if (nrOffDespawn == nrOf)
	{
		allHaveDespawned = true;
		nrOffDespawn = 0;
		if (nrOf < 50)
		{
			nrOf += 5;
		}
	}
	return allHaveDespawned;
}

void initiateText(sf::Font& font, sf::Text& text)
{
	font.loadFromFile("C:/Windows/fonts/arial.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Green);
	text.setPosition(500.0f, 100.0f);
}
