#include <SFML/Graphics.hpp>
#include <math.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(400,400), "Wave 2", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	float angle = 0.0f;
	int range = 50;
	float centerY = window.getSize().x / 2.0f;
	float xSpeed = 1.0f;
	float ySpeed = 0.05f;
	float xPos = 0;
	float yPos = centerY;

	std::vector<sf::Vertex> vertices;

	//Set window's background color
	window.clear(sf::Color::White);

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
		xPos += xSpeed;
		angle += ySpeed;
		yPos = centerY + std::sin(angle) * range;

		vertices.push_back(sf::Vertex(sf::Vector2f(xPos, yPos), sf::Color::Black));

		//Because we are constantly pushing vertices to be drawn, You can either clear or not the buffer.
		window.clear(sf::Color::White);
		window.draw(&vertices[0], vertices.size(), sf::LinesStrip);
		window.display();
	}

	return 0;
}