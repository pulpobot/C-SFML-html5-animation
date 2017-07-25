#include <SFML/Graphics.hpp>
#include "ColorScale.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Gradient Fill Radial", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(1);

	const int SIZE = 100;
	ColorScale gradient;
	gradient.insert(0.0, sf::Color::Black);
	gradient.insert(1, sf::Color::Transparent);
	sf::Image image = sf::Image();
	image.create(SIZE, SIZE);
	gradient.draw(image, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(SIZE*0.9f, SIZE*0.9f), SIZE, GradientStyle::Circle);

	sf::Texture texture;

	if (!texture.loadFromImage(image))
		return -1;

	sf::Sprite sprite = sf::Sprite(texture);
	sprite.setPosition(sf::Vector2f(100.0f, 100.0f));
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