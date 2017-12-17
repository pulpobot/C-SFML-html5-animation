#include "SFML\Graphics.hpp"
#include <iostream>
#include "Arrow.h"
#include <cmath>

#define M_PI	3.14159265358979323846

int main() 
{
	sf::RenderWindow window(sf::VideoMode(800,600), "Rotate To Mouse", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	
	Arrow arrow(window.getSize().x/2.0f, window.getSize().y / 2.0f);

	sf::Clock ticker;
	sf::Time deltaTime;
	float dx = 0.0f;
	float dy = 0.0f;

	while (window.isOpen()) 
	{
		deltaTime = ticker.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseMoved:
					dx = event.mouseMove.x - arrow.shape.getPosition().x;
					dy = event.mouseMove.y - arrow.shape.getPosition().y;
					break;
			}
		}
		//Clear the buffer
		window.clear(sf::Color::White);
		//Rotate arrow towards mouse (setRotation recieves degrees not radians)
		arrow.shape.setRotation((std::atan2(dy,dx)) * 180 / M_PI);
		//Draw shape
		window.draw(arrow.shape);
		//Display
		window.display();
	}
}