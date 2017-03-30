#pragma once
#include "SFML\Graphics.hpp"

class Arrow
{
public:
	Arrow(float x, float y);
	~Arrow();

	sf::ConvexShape shape;
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
};

