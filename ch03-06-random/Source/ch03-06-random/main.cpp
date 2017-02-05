#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <math.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Random", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	float angleX = 0;
	float angleY = 0;
	int range = 50;
	float centerX = window.getSize().x / 2.0f;
	float centerY = window.getSize().y / 2.0f;
	float xSpeed = 0.07f;
	float ySpeed = 0.11f;

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

		angleX += xSpeed;
		angleY += ySpeed;
		ball->shape.setPosition(centerX + std::sinf(angleX) * range, centerY + std::sinf(angleY) * range);

		window.clear(sf::Color::White);
		window.draw(ball->shape);
		window.display();
	}


}