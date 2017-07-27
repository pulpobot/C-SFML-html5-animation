#include "Ship.h"

Ship::Ship(float x, float y)
{
	shape.setPointCount(4);
	shape.setPoint(0, sf::Vector2f(10, 0));
	shape.setPoint(1, sf::Vector2f(-10, 10));
	shape.setPoint(2, sf::Vector2f(-5, 0));
	shape.setPoint(3, sf::Vector2f(-10, -10));

	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color::White);

	flame.setPointCount(4);
	flame.setPoint(0, sf::Vector2f(-5.1f, 0));
	flame.setPoint(1, sf::Vector2f(-8.0f, -5));
	flame.setPoint(2, sf::Vector2f(-15, 0));
	flame.setPoint(3, sf::Vector2f(-8.0f, 5));

	flame.setPosition(x, y);
	flame.setFillColor(sf::Color::Transparent);
	flame.setOutlineThickness(1);
	flame.setOutlineColor(sf::Color::White);
	showFlame = false;
}

Ship::~Ship()
{
}

void Ship::Draw(sf::RenderWindow * render)
{
	render->draw(shape);
	if (showFlame)
		render->draw(flame);
}

void Ship::SetPosition(float x, float y)
{
	shape.setPosition(sf::Vector2f(x, y));
	flame.setPosition(sf::Vector2f(x, y));
}

void Ship::SetX(float x)
{
	shape.setPosition(sf::Vector2f(x, shape.getPosition().y));
	flame.setPosition(sf::Vector2f(x, flame.getPosition().y));
}

void Ship::SetY(float y)
{
	shape.setPosition(sf::Vector2f(shape.getPosition().x, y));
	flame.setPosition(sf::Vector2f(flame.getPosition().x, y));
}

float Ship::GetX()
{
	return shape.getPosition().x;
}

float Ship::GetY()
{
	return shape.getPosition().y;
}

void Ship::Translate(float x, float y)
{
	shape.setPosition(sf::Vector2f(shape.getPosition().x + x, shape.getPosition().y + y));
	flame.setPosition(sf::Vector2f(flame.getPosition().x + x, flame.getPosition().y + y));
}

void Ship::SetRotation(float angle)
{
	shape.setRotation(angle);
	flame.setRotation(angle);
}

float Ship::GetRotation()
{
	return shape.getRotation();
}

void Ship::Rotate(float angle)
{
	shape.setRotation(shape.getRotation() + angle);
	flame.setRotation(flame.getRotation() + angle);
}