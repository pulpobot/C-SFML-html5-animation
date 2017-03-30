#include <SFML/Graphics.hpp>
#include "Arrow.h"

#define PI 3.14159265

int main()
{
	//You can turn off antialiasing if your graphics card doesn't support it
	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(400,400), "Rotational Velocity", sf::Style::Titlebar | sf::Style::Close, context);
	window.setFramerateLimit(60);
	
	Arrow arrow = Arrow(window.getSize().x / 2, window.getSize().y / 2);

	float vr = 2;

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

		arrow.Rotate(vr);

		window.clear(sf::Color::White);
		window.draw(arrow.shape);
		window.display();

	}

	return 0;
}