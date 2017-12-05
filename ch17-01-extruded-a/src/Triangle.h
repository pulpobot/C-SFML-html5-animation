#pragma once
#include "SFML\Graphics.hpp"
#include "Point3d.h"
#include <string>

class Triangle
{
public:
	Triangle(Point3d &a, Point3d &b, Point3d &c, sf::Color color = sf::Color::Red);
	~Triangle();
	Point3d *pointA;
    Point3d *pointB;
    Point3d *pointC;
    sf::Color fillColor;
    sf::Color lineColor;
    float lineWidth = 1;
    float alpha = 1.0f;

	void Draw(sf::RenderWindow &window);
	bool IsBackface();
};