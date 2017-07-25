#include <SFML/Graphics.hpp>
#include <cmath>
#include "Arrow.h"

#define PI 3.14159265

int main()
{
	//You can turn off antialiasing if your graphics card doesn't support it
	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(400,400), "Follow Mouse 2", sf::Style::Titlebar | sf::Style::Close, context);
	window.setFramerateLimit(60);
	
	Arrow arrow = Arrow(window.getSize().x / 2, window.getSize().y / 2);

	float ax = 0.0f;
	float ay = 0.0f;
	float vx = 0.0f;
	float vy = 0.0f;
	float dx = 0.0f;
	float dy = 0.0f;
	float angle = 0.0f;
	float force = 0.05f;

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
		ax = std::cos(angle) * force;
		ay = std::sin(angle) * force;

		vx += ax;
		vy += ay;
		arrow.Translate(vx, vy);
		arrow.SetRotation(angle * 180 / PI);

		window.clear(sf::Color::White);
		window.draw(arrow.shape);
		window.display();

	}

	return 0;
}