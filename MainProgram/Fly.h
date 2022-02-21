#pragma once
#include<SFML/Graphics.hpp>

class Fly :public sf::Drawable
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	float xSpeed;
	float windowHeight;
	float windowWidth;
	int damage;
public:
	Fly();

	void spawn();
	void setPosition(float xPos, float yPos);
	void setWindow(float windowHeight, float windowWidth);
	float getXposition()const;
	int getDamage()const;
	//sätter flugan utanför fönstret och xSPeed till 0
	void deSpawn();
	void move();
	sf::FloatRect getBounds()const;


	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};