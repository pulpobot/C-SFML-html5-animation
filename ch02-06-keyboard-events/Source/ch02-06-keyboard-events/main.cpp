#include "SFML\Graphics.hpp"
#include <iostream>
int main() 
{
	sf::Window window(sf::VideoMode(800,600), "Event Handling", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

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
					std::cout << "Key Down" << std::endl;
					break;
				case sf::Event::KeyReleased:
					std::cout << "Key Up" << std::endl;
					break;
			}
		}
	}
}