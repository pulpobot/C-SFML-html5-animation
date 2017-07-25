#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.h"

int main()
{
	//You can turn off antialiasing if your graphics card doesn't support it
	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(400,400), "Curve Through Point", sf::Style::Titlebar | sf::Style::Close, context);
	window.setFramerateLimit(60);

	std::vector<sf::Vertex> bezierCurvePoints;
	Utils::Bezier::QuadraticBezierCurve(sf::Vector2f(100, 200), sf::Vector2f(200,200), sf::Vector2f(300, 200), 20, bezierCurvePoints, sf::Color::Red, true);

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
				case sf::Event::MouseMoved:
					//While the mouse button is being pressed, add a new vertex to the current line with the mouse position
					Utils::Bezier::QuadraticBezierCurve(sf::Vector2f(100, 200), sf::Vector2f(event.mouseMove.x, event.mouseMove.y), sf::Vector2f(300, 200), 20, bezierCurvePoints, sf::Color::Red, true);
					break;
			}
		}

		window.clear(sf::Color::White);

		window.draw(&bezierCurvePoints[0], bezierCurvePoints.size(), sf::LinesStrip);

		window.display();
	}

	return 0;
}