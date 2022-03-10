#pragma once
#include<SFML/Graphics.hpp>
#include<string>
#include <stdlib.h>


class GameEntity : public sf::Drawable
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Shape* shape;

	float windowWidth;
	float windowHeight;
	sf::Vector2f velocity;
	bool isAlive;
	int radius;
	float fps;
protected:
	void moveSprite();
public:
	GameEntity(float windowWidth, float windowHeight, std::string fileName, sf::Vector2f speed, int radius, int color = 0);
	virtual~GameEntity();
	bool collideWith(const GameEntity& other);

	void setFPS(float fps);
	bool collideWithRect(const sf::RectangleShape other);
	bool collideWithFloat(const sf::FloatRect& other);
	void setPosition(float xPos, float yPos);
	sf::FloatRect getBounds()const;
	float getWindowWidth();
	float getWindowHeight();
	float getSpeed();
	sf::Vector2f getVelocity();
	sf::Vector2f getPosition();
	float getRadius();
	void setVelocity(sf::Vector2f newVelocity);


	virtual void move() = 0;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};