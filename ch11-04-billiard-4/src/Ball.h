#pragma once
#include "SFML\Graphics.hpp"
#include <string>

class Ball
{
public:
	Ball(float x, float y, float radius, sf::Color color);	
	~Ball();

	sf::CircleShape shape;
    std::string id;
	float vx;
	float vy;
    float mass = 1;
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

