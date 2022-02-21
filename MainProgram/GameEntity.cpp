#include "GameEntity.h"

void GameEntity::moveSprite(sf::Vector2f speed)
{
	this->shape->move(speed);
}

GameEntity::GameEntity(float windowWidth, float windowHeight, std::string fileName, sf::Vector2f speed)
	:windowHeight(windowHeight),windowWidth(windowWidth), speed(speed)
{
	if (fileName == "Ball")
	{
		this->shape = new sf::CircleShape(100);
		this->shape->setFillColor(sf::Color::Blue);
		this->shape->setOrigin(0, 0);
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
	return this->sprite.getGlobalBounds().intersects(other.getBounds());
}



void GameEntity::increaseScale()
{
	this->sprite.setScale(this->sprite.getScale() * 1.25f);
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
	this->sprite.setPosition(xPos, yPos);
}

void GameEntity::Spawn(float xPos, float yPos)
{
	this->sprite.setPosition(xPos, yPos);
	this->isAlive = true;
}

bool GameEntity::getIsSpawned() const
{
	return this->isAlive;
}

sf::FloatRect GameEntity::getBounds() const
{
	return this->sprite.getGlobalBounds();
}


void GameEntity::disapear()
{
	this->sprite.setPosition(-300.0f, -300.0f);
	this->isAlive = false;
}

float GameEntity::getWindowWidth()
{
	return windowWidth;
}

float GameEntity::getWindowHeight()
{
	return windowHeight;
}

void GameEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*this->shape);
}
