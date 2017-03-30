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
	float GetX();
	float GetY();
	///Increase current position by x and y values
	void Translate(float x, float y);
	///Overrides current rotation (in degrees)
	void SetRotation(float angle);
	///Increase current rotation by an anglee (in degrees)
	void Rotate(float angle);


};

