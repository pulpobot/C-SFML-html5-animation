#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.h"

//has to be an odd number
const int MAX_POINTS = 9;

void ResetPoints(std::vector<sf::Vertex> &curvePoints, int maxWidth, int maxHeight)
{
	//Set the seed
	std::srand(time(NULL));
	
	std::vector<sf::Vector2f> points;

	//Generate some random points
	for (short i = 0; i < MAX_POINTS; i++)
	{
		points.push_back(sf::Vector2f(std::rand() % maxWidth, std::rand() % maxHeight));
	}

	for (short i = 0; i < MAX_POINTS-2; i = i + 2)
	{
		Utils::Bezier::AccumulativeQuadraticBezierCurve(points[i], points[i+1], points[i+2], 20, curvePoints, sf::Color::Black);
	}
}

int main()
{
	//You can turn off antialiasing if your graphics card doesn't support it
	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(400,400), "Multi Curve 1", sf::Style::Titlebar | sf::Style::Close, context);
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