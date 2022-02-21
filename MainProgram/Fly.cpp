#include "Fly.h"

Fly::Fly()
{
	if (rand() % 2 == 0)
	{
		this->texture.loadFromFile("../Images/litenFluga.jpg");
		this->sprite.setTexture(this->texture);
		this->damage = 1;
	}
	else
	{
		this->texture.loadFromFile("../Images/storFluga.jpg");
		this->sprite.setTexture(this->texture);
		this->damage = 2;
	}
	this->xSpeed = 0.0f;
	this->windowHeight = 0.0f;
	this->windowWidth = 0.0f;

}

void Fly::spawn()
{
	this->sprite.setPosition(this->windowWidth, (float)(rand() % (int)this->windowHeight));
	//this->sprite.setPosition(0.0f - this->sprite.getGlobalBounds().width, (float)(rand() % (int)this->windowHeight));
	this->xSpeed = -(float)(rand() % 5 + 3);
}

void Fly::setPosition(float xPos, float yPos)
{
	this->sprite.setPosition(xPos, yPos);
}

void Fly::setWindow(float windowHeight, float windowWidth)
{
	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;
}

float Fly::getXposition() const
{
	return this->sprite.getGlobalBounds().left;
}

int Fly::getDamage() const
{
	return this->damage;
}

void Fly::deSpawn()
{
	this->sprite.setPosition(100.0f, -100.0f);
	this->xSpeed = 0.0f;
}

void Fly::move()
{
	this->sprite.move(this->xSpeed, 0.0f);
}

sf::FloatRect Fly::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Fly::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}
