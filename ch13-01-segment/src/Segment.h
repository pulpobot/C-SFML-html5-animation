#pragma once
#include "SFML\Graphics.hpp"
#include <string>

class Segment
{
public:
	Segment(float width, float height, sf::Color color = sf::Color::White);
	~Segment();

	sf::ConvexShape shape;
    sf::CircleShape leftPin;
    sf::CircleShape rightPin;
    std::string id;
    float width = 0;
    float height = 0;
	float vx;
	float vy;
	///Overrides current position
    void SetPosition(sf::Vector2f pos);
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
    void Draw(sf::RenderWindow &renderWindow);
    void UpdatePinsPosition();
    sf::Vector2f GetPin();
	sf::FloatRect GetBounds();
};

