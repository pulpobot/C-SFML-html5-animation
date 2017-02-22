#include <SFML/Graphics.hpp>
#include "ColorScale.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Gradient Fill 1", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(1);

	const int SIZE = 100;
	ColorScale gradient;
	gradient.insert(0.0, sf::Color::White);
	gradient.insert(1, sf::Color::Red);
	sf::Image image = sf::Image();
	image.create(SIZE, SIZE);
	gradient.draw(image, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(SIZE, SIZE), SIZE, GradientStyle::Linear);

	sf::Texture texture;

	if (!texture.loadFromImage(image))
		return -1;

	sf::Sprite sprite = sf::Sprite(texture);

	window.clear(sf::Color::White);
	window.draw(sprite);
	window.display();

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

	}

	return 0;
}