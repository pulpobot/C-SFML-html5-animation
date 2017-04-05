#include <SFML/Graphics.hpp>
#include "Ball.h"
const float GRAVITY = 0.02f;

int main()
{
	//You can turn off antialiasing if your graphics card doesn't support it
	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(400,400), "Gravity", sf::Style::Titlebar | sf::Style::Close, context);
	window.setFramerateLimit(60);
	
	Ball ball = Ball(window.getSize().x / 2, window.getSize().y / 2, 40, sf::Color::Red);

	float ax = 0;
	float ay = 0;
	float vx = 0;
	float vy = 0;

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
					switch (event.key.code) 
					{
					case sf::Keyboard::Left:
						ax = -0.1f;
						break;
					case sf::Keyboard::Right:
						ax = 0.1f;
						break;
					case sf::Keyboard::Up:
						ay = -0.1f;
						break;
					case sf::Keyboard::Down:
						ay = 0.1f;
						break;
					}
					break;
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Left:
					case sf::Keyboard::Right:
						ax = 0.0f;
						break;
					case sf::Keyboard::Up:
					case sf::Keyboard::Down:
						ay = 0.0f;
						break;
					}
					break;
			}
		}

		vx += ax;
		vy += ay;
		vy += GRAVITY;
		ball.Translate(vx,vy);
		window.clear(sf::Color::White);
		window.draw(ball.shape);
		window.display();

	}

	return 0;
}