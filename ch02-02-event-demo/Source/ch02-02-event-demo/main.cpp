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
				case sf::Event::MouseButtonPressed:
					std::cout << "Mouse Down\n";
					break;
				case sf::Event::MouseButtonReleased:
					std::cout << "Mouse Up\n";
					break;
			}
		}
	}
}