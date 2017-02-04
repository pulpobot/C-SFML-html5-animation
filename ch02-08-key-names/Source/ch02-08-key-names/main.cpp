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
					case sf::Keyboard::Left:
						std::cout << "Left!\n";
						break;
					case sf::Keyboard::Right:
						std::cout << "Right!\n";
						break;
					case sf::Keyboard::Up:
						std::cout << "Up!\n";
						break;
					case sf::Keyboard::Down:
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