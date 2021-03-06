#include "GameEntity.h"
#include <iostream>

void GameEntity::moveSprite()
{
	//this->shape->move(velocity.x* this->timeConstant, this->velocity.y* timeConstant);
	this->shape->move(velocity.x, this->velocity.y);
}

GameEntity::GameEntity(float windowWidth, float windowHeight, std::string fileName, sf::Vector2f speed, int radius, int color)
	:windowHeight(windowHeight),windowWidth(windowWidth), velocity(speed), radius(radius), fps(60.f), timeConstant(1.f)
{

	if (fileName == "Ball")
	{
		this->shape = new sf::CircleShape(radius);
		//this->shape->setFillColor(sf::Color::Blue);
		this->shape->setPosition(0, windowHeight-this->shape->getGlobalBounds().height);

		int r, g, b;
		if (color == 0)
		{
			//color = rand() % 6 + 1;
			r = rand() % 256;
			g = rand() % 256;
			b = rand() % 256;
		}

		switch (color)
		{
		default:
			this->shape->setFillColor(sf::Color::Blue);
			break;
		case 0:
			//this->shape->setFillColor(sf::Color::Blue);
			this->shape->setFillColor(sf::Color::Color(r, g, b));
			break;
		}

		//switch (color)
		//{
		//default:
		//	this->shape->setFillColor(sf::Color::Blue);
		//	break;
		//case 0:
		//	//this->shape->setFillColor(sf::Color::Blue);
		//	this->shape->setFillColor(sf::Color::Color(r, g, b));
		//	break;
		//case 1:
		//	this->shape->setFillColor(sf::Color::Blue);
		//	break;
		//case 2:
		//	this->shape->setFillColor(sf::Color::Magenta);
		//	break;
		//case 3:
		//	this->shape->setFillColor(sf::Color::Yellow);
		//	break;
		//case 4:
		//	this->shape->setFillColor(sf::Color::Cyan);
		//	break;
		//case 5:
		//	this->shape->setFillColor(sf::Color::Green);
		//	break;
		//case 6:
		//	this->shape->setFillColor(sf::Color::Red);
		//	break;
		//}
	}
	/*if (this->texture.loadFromFile("../Images/" + fileName))
	{
		this->sprite.setTexture(this->texture);
	}
	this->isAlive = false;
	this->rect = sf::IntRect(0, 0, this->texture.getSize().x, this->texture.getSize().y);
	this->sprite.setTextureRect(rect);*/
}

GameEntity::~GameEntity()
{
}

bool GameEntity::collideWith(const GameEntity& other)
{
	return this->shape->getGlobalBounds().intersects(other.shape->getGlobalBounds());
}


void GameEntity::setFPS(float framesPerSecond)
{
	this->fps = framesPerSecond;
	timeConstant = (1.f / fps)/ (1.f / 60.f);
	std::cout << "TimeConstant: " << timeConstant << std::endl;
}

bool GameEntity::collideWithRect(const sf::RectangleShape other)
{
	return this->sprite.getGlobalBounds().intersects(other.getGlobalBounds());
}

bool GameEntity::collideWithFloat(const sf::FloatRect& other)
{
	return this->sprite.getGlobalBounds().intersects(other);
}

void GameEntity::setPosition(float xPos, float yPos)
{
	this->shape->setPosition(xPos, yPos);
}

sf::FloatRect GameEntity::getBounds() const
{
	return this->shape->getGlobalBounds();
}


float GameEntity::getWindowWidth()
{
	return windowWidth;
}

float GameEntity::getWindowHeight()
{
	return windowHeight;
}

float GameEntity::getSpeed()
{
	return sqrt(velocity.x* velocity.x + velocity.y* velocity.y);
}

sf::Vector2f GameEntity::getVelocity()
{
	return this->velocity;
}

sf::Vector2f GameEntity::getPosition()
{
	return sf::Vector2f(this->shape->getGlobalBounds().left+this->shape->getGlobalBounds().width/2, this->shape->getGlobalBounds().top + this->shape->getGlobalBounds().height / 2);
}

float GameEntity::getRadius()
{
	//Convert from cm to m
	return (this->radius)*(1.f/100.f);
}

void GameEntity::setVelocity(sf::Vector2f newVelocity)
{
	this->velocity = newVelocity;
}

void GameEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*this->shape);
}
