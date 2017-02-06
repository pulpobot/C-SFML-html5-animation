#pragma once
#include "SFML\Graphics.hpp"
class Utils
{
public:
	static void Utils::QuadraticBezierCurve(const sf::Vector2f &p0, const sf::Vector2f &p1, sf::Vector2f &p2, int segments, std::vector<sf::Vector2f> &curvePoints);
	static void Utils::QuadraticBezierCurve(const sf::Vector2f &p0, const sf::Vector2f &p1, sf::Vector2f &p2, int segments, std::vector<sf::Vertex> &curvePoints, sf::Color lineColor);
private:
	// Disallow creating an instance of this object
	Utils() {}
};

