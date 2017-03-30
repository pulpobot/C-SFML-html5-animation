#include <SFML/Graphics.hpp>
#include "Ball.h"

int main()
{
	//You can turn off antialiasing if your graphics card doesn't support it
	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(400,400), "Acceleration 1", sf::Style::Titlebar | sf::Style::Close, context);
	window.setFramerateLimit(60);
	
	Ball ball = Ball(50, 100, 40, sf::Color::Red);

	float ax = 0.1f;
	float vx = 0;

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

		vx += ax;
		ball.Translate(vx,0);

		window.clear(sf::Color::White);
		window.draw(ball.shape);
		window.display();

	}

	return 0;
}