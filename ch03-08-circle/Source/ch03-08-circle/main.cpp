#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <math.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Circle", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	float angle = 0;
	float centerX = window.getSize().x / 2.0f;
	float centerY = window.getSize().y / 2.0f;
	int radius = 50;
	float speed = 0.05f;

	Ball * ball = new Ball(centerX, centerY, 40, sf::Color::Red);

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

		angle += speed;
		ball->shape.setPosition(centerX + std::cosf(angle) * radius, centerY + std::sinf(angle) * radius);

		window.clear(sf::Color::White);
		window.draw(ball->shape);
		window.display();
	}


}