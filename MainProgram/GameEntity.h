#pragma once
#include<SFML/Graphics.hpp>
#include<string>


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
protected:
	void moveSprite();
public:
	GameEntity(float windowWidth, float windowHeight, std::string fileName, sf::Vector2f speed, int radius);
	virtual~GameEntity();
	bool collideWith(const GameEntity& other);

	void increaseScale();
	bool collideWithRect(const sf::RectangleShape other);
	bool collideWithFloat(const sf::FloatRect& other);
	void setPosition(float xPos, float yPos);
	void Spawn(float xPos, float yPos); //sets isAlive = true
	bool getIsSpawned()const;
	sf::FloatRect getBounds()const;
	void disapear();//use if they need to despawn
	float getWindowWidth();
	float getWindowHeight();
	float getSpeed();
	sf::Vector2f getVelocity();
	float getRadius();
	void setVelocity(sf::Vector2f newVelocity);


	virtual void move() = 0;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};