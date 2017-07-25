#include "Utils.h"

void Utils::Bezier::QuadraticBezierCurve(const sf::Vector2f &p0, const sf::Vector2f &p1, sf::Vector2f &p2, int segments, std::vector<sf::Vector2f> &curvePoints)
{
	//If there are any segments required
	if (segments <= 0)
		return;

	//Quadratic Bezier Curve Math Formula: (1 - t)*((1-t)*p0 + t*p1) + t*((1-t)*p1 + t*p2);
	curvePoints.clear();
	float stepIncreasement = 1.0f / segments;
	float t = 0.0f;
	float px = 0.0f;
	float py = 0.0f;

	for (int i = 0; i <= segments; i++)
	{
		px = (1.0f - t)*((1.0f - t)*p0.x + t*p1.x) + t*((1.0f - t)*p1.x + t*p2.x);
		py = (1.0f - t)*((1.0f - t)*p0.y + t*p1.y) + t*((1.0f - t)*p1.y + t*p2.y);
		curvePoints.push_back(sf::Vector2f(px, py));
		t += stepIncreasement;
	}
}

void Utils::Bezier::QuadraticBezierCurve(const sf::Vector2f &p0, const sf::Vector2f &p1, sf::Vector2<float> p2, int segments, std::vector<sf::Vertex> &curvePoints, sf::Color lineColor)
{
	//If there are any segments required
	if (segments <= 0)
		return;

	//Quadratic Bezier Curve Math Formula: (1 - t)*((1-t)*p0 + t*p1) + t*((1-t)*p1 + t*p2);
	curvePoints.clear();
	float stepIncreasement = 1.0f / segments;
	float t = 0;
	float px = 0;
	float py = 0;

	//Add points based on control point's position
	for (int i = 0; i <= segments; i++)
	{
		px = (1.0f - t)*((1.0f - t)*p0.x + t*p1.x) + t*((1.0f - t)*p1.x + t*p2.x);
		py = (1.0f - t)*((1.0f - t)*p0.y + t*p1.y) + t*((1.0f - t)*p1.y + t*p2.y);
		curvePoints.push_back(sf::Vertex(sf::Vector2f(px, py), lineColor));
		t += stepIncreasement;
	}
}