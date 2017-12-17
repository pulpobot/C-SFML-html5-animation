#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <cmath>

int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Bobbing 1", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	Ball ball(window.getSize().x / 2.0f, window.getSize().y / 2.0f, 40, sf::Color::Red);
	float angle = 0;
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

		angle += 0.1f;
		ball.shape.setPosition(ball.shape.getPosition().x, window.getSize().y / 2 + std::sin(angle) * 50);

		window.clear(sf::Color::White);
		window.draw(ball.shape);
		window.display();
	}


}