#pragma once
#include<SFML/Graphics.hpp>
#include"Fly.h"

class Tomato :public sf::Drawable
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	int health;
	float windowWidth;
	float windowHeight;

public:
	Tomato(float windowHeight, float windowWidth);

	void move();
	bool isHit(const Fly flies)const;
	int getHealth()const;
	void decreaseHealth(Fly flies);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};