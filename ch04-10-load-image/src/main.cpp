#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Load Image", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(1);

	sf::Texture texture;
	if (!texture.loadFromFile("res/picture.jpg"))
		return -1;

	sf::Sprite sprite = sf::Sprite(texture);
	sprite.setPosition(sf::Vector2f(0.0f, 0.0f));
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