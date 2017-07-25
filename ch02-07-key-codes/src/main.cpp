#include "SFML\Graphics.hpp"
#include <iostream>
int main() 
{
	sf::Window window(sf::VideoMode(800,600), "Key Codes", sf::Style::Titlebar | sf::Style::Close);
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
					switch (event.key.code)
					{
					case 71:
						std::cout << "Left!\n";
						break;
					case 72:
						std::cout << "Right!\n";
						break;
					case 73:
						std::cout << "Up!\n";
						break;
					case 74:
						std::cout << "Down!\n";
						break;
					default:
						std::cout << event.key.code << std::endl;
						break;
					}
			}
		}
	}
}