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

void Arrow::SetPosition(float x, float y)
{
	shape.setPosition(sf::Vector2f(x, y));
}

void Arrow::SetX(float x)
{
	shape.setPosition(sf::Vector2f(x, shape.getPosition().y));
}

void Arrow::SetY(float y)
{
	shape.setPosition(sf::Vector2f(shape.getPosition().x, y));
}

float Arrow::GetX()
{
	return shape.getPosition().x;
}

float Arrow::GetY()
{
	return shape.getPosition().y;
}

void Arrow::Translate(float x, float y)
{
	shape.setPosition(sf::Vector2f(shape.getPosition().x + x, shape.getPosition().y + y));
}

void Arrow::SetRotation(float angle)
{
	shape.setRotation(angle);
}
