#include "Arrow.h"

Arrow::Arrow(float x, float y)
{
	shape.setPointCount(7);
	shape.setPoint(0, sf::Vector2f(0, -25));
	shape.setPoint(1, sf::Vector2f(0, -50));
	shape.setPoint(2, sf::Vector2f(50, 0));
	shape.setPoint(3, sf::Vector2f(0, 50));
	shape.setPoint(4, sf::Vector2f(0, 25));
	shape.setPoint(5, sf::Vector2f(-50, 25));
	shape.setPoint(6, sf::Vector2f(-50, -25));

	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::Yellow);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Black);
}


Arrow::~Arrow()
{
}
