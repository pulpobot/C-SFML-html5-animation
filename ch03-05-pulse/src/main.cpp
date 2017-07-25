#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <cmath>

int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Pulse", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	float angle = 0;
	float centerScale = 1;
	float range = 0.5f;
	float speed = 0.05f;

	Ball * ball = new Ball(window.getSize().x / 2.0f, window.getSize().y / 2.0f, 40, sf::Color::Red);

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
		ball->shape.setScale(centerScale + std::sin(angle) * range, centerScale + std::sin(angle) * range);

		window.clear(sf::Color::White);
		window.draw(ball->shape);
		window.display();
	}


}