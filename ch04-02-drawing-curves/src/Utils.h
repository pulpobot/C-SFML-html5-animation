#pragma once
#include "SFML\Graphics.hpp"
namespace Utils {
	namespace Bezier {
		void QuadraticBezierCurve(const sf::Vector2f &p0, const sf::Vector2f &p1, sf::Vector2f &p2, int segments, std::vector<sf::Vector2f> &curvePoints);
		void QuadraticBezierCurve(const sf::Vector2f &p0, const sf::Vector2f &p1, sf::Vector2<float> p2, int segments, std::vector<sf::Vertex> &curvePoints, sf::Color lineColor);
	}
}
