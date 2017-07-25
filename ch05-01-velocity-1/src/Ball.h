#pragma once
#include "SFML\Graphics.hpp"

class Ball
{
public:
	Ball(float x, float y, float radius, sf::Color color);	
	~Ball();

	sf::CircleShape shape;
	///Overrides current position
	void SetPosition(float x, float y);
	void SetX(float x);
	void SetY(float y);
	///Increase current position by x and y values
	void Translate(float x, float y);

};

