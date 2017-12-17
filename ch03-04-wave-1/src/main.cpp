#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <cmath>

int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Wave 1", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	float angle = 0;
	float xSpeed = 1.0f;
	float ySpeed = 0.05f;
	float range = 50;
	float centerY = window.getSize().y / 2.0f;

	Ball ball(0, centerY, 40, sf::Color::Red);

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
			}
		}

		angle += ySpeed;
		ball.shape.setPosition(ball.shape.getPosition().x + xSpeed, centerY + std::sin(angle) * range);

		window.clear(sf::Color::White);
		window.draw(ball.shape);
		window.display();
	}
}