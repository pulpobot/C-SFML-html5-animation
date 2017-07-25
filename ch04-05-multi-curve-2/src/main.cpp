#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.h"

//needs to be at least 3
const int MAX_POINTS = 9;

void ResetPoints(std::vector<sf::Vertex> &curvePoints, int maxWidth, int maxHeight)
{
	if (MAX_POINTS < 3)
		return;

	//Set the seed
	std::srand(time(NULL));
	
	std::vector<sf::Vector2f> points;
	std::vector<sf::Vector2f> ctrlPoints;

	//Generate some random points
	for (short i = 0; i < MAX_POINTS; i++)
	{
		points.push_back(sf::Vector2f(std::rand() % maxWidth, std::rand() % maxHeight));
		//Obtain the midpoints for each pair of points
		if (i>0) 
		{
			ctrlPoints.push_back(sf::Vector2f((points[i-1].x + points[i].x) / 2, (points[i-1].y + points[i].y) / 2));
		}
	}

	/*"first and last midpoints are not used, and the first and last original points
	remain terminal points for the curves. You need to make in-between points only for the second point up to
	the second-to-last point."*/
	Utils::Bezier::AccumulativeQuadraticBezierCurve(points[0], points[1], ctrlPoints[1], 20, curvePoints, sf::Color::Black);
	
	short i = 1;
	for (i; i < ctrlPoints.size()-2; i++)
	{
		Utils::Bezier::AccumulativeQuadraticBezierCurve(ctrlPoints[i], points[i+1], ctrlPoints[i+1], 20, curvePoints, sf::Color::Black);
	}

	Utils::Bezier::AccumulativeQuadraticBezierCurve(ctrlPoints[i], points[points.size() - 2], points[points.size()-1], 20, curvePoints, sf::Color::Black);

}

int main()
{
	//You can turn off antialiasing if your graphics card doesn't support it
	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(400,400), "Multi Curve 2", sf::Style::Titlebar | sf::Style::Close, context);
	window.setFramerateLimit(60);

	std::vector<sf::Vertex> bezierCurvePoints;
	ResetPoints(bezierCurvePoints, window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::R) 
					{
						//Repopulate the points each time the R key is pressed
						bezierCurvePoints.clear();
						ResetPoints(bezierCurvePoints, window.getSize().x, window.getSize().y);
					}
					break;
			}
		}

		window.clear(sf::Color::White);
		window.draw(&bezierCurvePoints[0], bezierCurvePoints.size(), sf::LinesStrip);
		window.display();
	}

	return 0;
}