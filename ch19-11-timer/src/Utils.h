#pragma once

#include <chrono>
#include "SFML\Graphics.hpp"
#include "Ball.h"

namespace Utils {
	namespace Bezier {
		void QuadraticBezierCurve(const sf::Vector2f &p0, sf::Vector2f &p1, sf::Vector2f &p2, int segments, std::vector<sf::Vector2f> &curvePoints, bool throughControlPoint = false);
		void QuadraticBezierCurve(const sf::Vector2f &p0, sf::Vector2f &p1, sf::Vector2f &p2, int segments, std::vector<sf::Vertex> &curvePoints, sf::Color lineColor, bool throughControlPoint = false);
		void AccumulativeQuadraticBezierCurve(const sf::Vector2f &p0, sf::Vector2f &p1, sf::Vector2f &p2, int segments, std::vector<sf::Vertex> &curvePoints, sf::Color lineColor, bool throughControlPoint = false);
	}

	bool ContainsPoint(sf::FloatRect rect, float x, float y);
	bool Intersects(sf::FloatRect rectA, sf::FloatRect rectB);

	struct Timer
	{
		typedef std::chrono::steady_clock clock ;
		typedef std::chrono::milliseconds milliseconds ;

		void reset() { start = clock::now() ; }

        void (*callback)(Ball &ball, sf::RenderWindow &window);

		unsigned long long seconds_elapsed() const
		{ return std::chrono::duration_cast<milliseconds>( clock::now() - start ).count() ; }

        void Execute(float fps, Ball &ball, sf::RenderWindow &window){
            if( seconds_elapsed() > 1000 / fps ){
                callback(ball, window);
                reset();
            }
        }

	private: clock::time_point start = clock::now() ;
	};
}
