#pragma once
#include "SFML\Graphics.hpp"
#include <string>

class Box
{
public:
    Box(float x, float y, sf::Vector2f size, sf::Color color);
    Box(float x, float y, float width, float height, sf::Color color) : Box(x, y, sf::Vector2f(width, height), color){}
	~Box();

	sf::RectangleShape shape;
    std::string id;
	float vx;
	float vy;
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
    void Draw(sf::RenderWindow &renderWindow, float gravity = 0);
	sf::FloatRect GetBounds();
};

