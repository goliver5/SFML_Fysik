#include "Tomato.h"
#include<iostream>

Tomato::Tomato(float windowHeight, float windowWidth)
{
	this->texture.loadFromFile("../Images/tomat.jpg");
	this->sprite.setTexture(this->texture);
	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;
	this->health = 10;
}

void Tomato::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->sprite.getGlobalBounds().top > 0.0f)
	{
		this->sprite.move(0.0f, -6.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height < this->windowHeight)
	{
		this->sprite.move(0.0f, 6.0f);
	}
}

bool Tomato::isHit(const Fly flies) const
{
	return this->sprite.getGlobalBounds().intersects(flies.getBounds());
}

int Tomato::getHealth() const
{
	return this->health;
}

void Tomato::decreaseHealth(Fly flies)
{
	this->health = this->health - flies.getDamage();
	std::cout << this->health;
}

void Tomato::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}
