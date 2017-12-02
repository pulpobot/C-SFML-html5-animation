#pragma once
#include "SFML\Graphics.hpp"
#include <string>

class Ball3d
{
public:
	Ball3d(float x, float y, float z, float radius, sf::Color color);
	~Ball3d();

	sf::CircleShape shape;
	float vx;
	float vy;
	float vz;
    float xPos;
    float yPos;
    float zPos;
    bool visible = true;
	///Overrides current position
	void SetPosition(float x, float y, float z);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	float GetX();
	float GetY();
	float GetZ();
	///Increase current position by x and y values
	void Translate(float x, float y);
	///Overrides current rotation (in degrees)
	void SetRotation(float angle);
	///Increase current rotation by an anglee (in degrees)
	void Rotate(float angle);
    void Draw(sf::RenderWindow &renderWindow);
	sf::FloatRect GetBounds();
};

