#include "Ball.h"

Ball::Ball(float x, float y, float radius, sf::Color color)
{
	shape = sf::CircleShape(radius);
	shape.setFillColor(color);
	shape.setOrigin(radius, radius);
	shape.setPosition(x, y);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Black);
}


Ball::~Ball()
{
}
