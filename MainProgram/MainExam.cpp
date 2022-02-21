#include <SFML/Graphics.hpp>
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
	std::srand((unsigned)time(0));
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Fysik projekt");

	sf::Clock clock;
	sf::Time elapsedTimeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timePlayed = sf::Time::Zero;

	sf::Text text;
	sf::Font font;
	initiateText(font, text);


	int nrOfFliesSpawned = 5;
	int nrOffDespawn = 0;

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

				elapsedTimeSinceLastUpdate -= timePerFrame;

				text.setString("Time: " + std::to_string(timePlayed.asSeconds()));

			}
		window.clear();
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
	text.setPosition(500.0f, 100.0f);
}
