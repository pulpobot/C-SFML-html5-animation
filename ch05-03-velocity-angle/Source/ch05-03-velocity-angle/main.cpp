#include <SFML/Graphics.hpp>
#include "Ball.h"

#define PI 3.14159265

int main()
{
	//You can turn off antialiasing if your graphics card doesn't support it
	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(400,400), "Velocity Angle", sf::Style::Titlebar | sf::Style::Close, context);
	window.setFramerateLimit(60);
	
	Ball ball = Ball(50, 100, 40, sf::Color::Red);

	float angle = 45.0f;
	float speed = 1.0f;
	float vx = 0;
	float vy = 0;
	float radians;

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
		radians = angle * PI / 180;

		vx = std::cos(radians) * speed;
		vy = std::sin(radians) * speed;

		ball.Translate(vx, vy);

		window.clear(sf::Color::White);
		window.draw(ball.shape);
		window.display();

	}

	return 0;
}