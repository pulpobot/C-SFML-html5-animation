#pragma once
#include "SFML\Graphics.hpp"

class Arrow
{
public:
	Arrow(float x, float y);
	~Arrow();

	sf::ConvexShape shape;
};

