#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <cmath>

template <typename T>
std::string to_string(T value)
{
	//create an output string stream
	std::ostringstream os;

	//throw the value into the string stream
	os << value;

	//convert the string stream into a string and return
	return os.str();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(400,400), "Distance", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	sf::Font font;
	if (!font.loadFromFile("res/cour.ttf"))
	{
		std::cout << "Error loading cout.ttf file" << std::endl;
		return -1;
	}

	sf::Text instructionsText;
	instructionsText.setFont(font);
	instructionsText.setCharacterSize(15);
	instructionsText.setString("Move the mouse around");
	instructionsText.setFillColor(sf::Color::Black);
	instructionsText.setPosition(sf::Vector2f(10,10));

	sf::Text distanceText;
	distanceText.setFont(font);
	distanceText.setCharacterSize(15);
	distanceText.setFillColor(sf::Color::Black);
	distanceText.setPosition(sf::Vector2f(10, 30));

	sf::RectangleShape rect1(sf::Vector2f(4,4));
	rect1.setFillColor(sf::Color::Black);
	rect1.setOrigin(2, 2);
	rect1.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

	float dx = 0;
	float dy = 0;

	std::vector<sf::Vertex> directionLine;

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
				case sf::Event::MouseMoved:
					dx = rect1.getPosition().x - event.mouseMove.x;
					dy = rect1.getPosition().y - event.mouseMove.y;
					distanceText.setString("Distance: " + to_string(std::sqrt(dx * dx + dy * dy)));

					directionLine.clear();
					directionLine.push_back(sf::Vertex(sf::Vector2f(rect1.getPosition().x, rect1.getPosition().y), sf::Color::Black));
					directionLine.push_back(sf::Vertex(sf::Vector2f(event.mouseMove.x, event.mouseMove.y), sf::Color::Black));
					break;
			}
		}

		window.clear(sf::Color::White);
		window.draw(rect1);
		window.draw(instructionsText);
		window.draw(distanceText);
		window.draw(&directionLine[0], directionLine.size(), sf::LinesStrip);
		window.display();
	}

	return 0;
}