#pragma once
#include "SFML\Graphics.hpp"

class Ball
{
public:
	Ball(float x, float y, float radius, sf::Color color);
	~Ball();
	
	sf::CircleShape shape;
};

