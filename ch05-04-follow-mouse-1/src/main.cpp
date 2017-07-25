#include <SFML/Graphics.hpp>
#include <cmath>
#include "Arrow.h"

#define PI 3.14159265

int main()
{
	//You can turn off antialiasing if your graphics card doesn't support it
	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(400,400), "Follow Mouse 1", sf::Style::Titlebar | sf::Style::Close, context);
	window.setFramerateLimit(60);
	
	Arrow arrow = Arrow(50, 100);

	float angle = 45.0f;
	float speed = 3.0f;
	float dx = 0;
	float dy = 0;
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
			}
		}

		dx = event.mouseMove.x - arrow.GetX();
		dy = event.mouseMove.y - arrow.GetY();
		angle = std::atan2(dy, dx); //Radians

		vx = std::cos(angle) * speed;
		vy = std::sin(angle) * speed;

		arrow.SetRotation(angle * 180 / PI);
		arrow.Translate(vx, vy);

		window.clear(sf::Color::White);
		window.draw(arrow.shape);
		window.display();
	}

	return 0;
}