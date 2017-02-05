#include <SFML/Graphics.hpp>
#include <math.h>
#include <time.h>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(400,400), "Distance", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	sf::Font font;
	if (!font.loadFromFile("cour.ttf"))
	{
		std::cout << "Error loading cout.ttf file" << std::endl;
		return -1;
	}

	sf::Text instructionsText;
	instructionsText.setFont(font);
	instructionsText.setCharacterSize(15);
	instructionsText.setString("Press the R key to randomize the squares");
	instructionsText.setFillColor(sf::Color::Black);
	instructionsText.setPosition(sf::Vector2f(10,10));

	sf::Text distanceText;
	distanceText.setFont(font);
	distanceText.setCharacterSize(15);
	distanceText.setFillColor(sf::Color::Black);
	distanceText.setPosition(sf::Vector2f(10, 30));

	//Set a seed for the random generator
	std::srand(std::time(NULL));

	sf::RectangleShape rect1(sf::Vector2f(4,4));
	rect1.setFillColor(sf::Color::Black);
	//Get random values between 0.01 and 1.0
	float xRand = (std::rand() % 100 + 1) / 100.0f;
	float yRand = (std::rand() % 100 + 1) / 100.0f;
	rect1.setPosition(sf::Vector2f(window.getSize().x * xRand - 2, window.getSize().y * yRand - 2));

	sf::RectangleShape rect2(sf::Vector2f(4, 4));
	rect2.setFillColor(sf::Color::Red);
	xRand = (std::rand() % 100 + 1) / 100.0f;
	yRand = (std::rand() % 100 + 1) / 100.0f;
	rect2.setPosition(sf::Vector2f(window.getSize().x * xRand - 2, window.getSize().y * yRand - 2));


	float dx = rect2.getPosition().x - rect1.getPosition().x;
	float dy = rect2.getPosition().y - rect1.getPosition().y;

	distanceText.setString("Distance: " + std::to_string(std::sqrt(dx * dx + dy * dy)));

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
					if (event.key.code == sf::Keyboard::R) 
					{
						xRand = (std::rand() % 100 + 1) / 100.0f;
						yRand = (std::rand() % 100 + 1) / 100.0f;
						rect1.setPosition(sf::Vector2f(window.getSize().x * xRand - 2, window.getSize().y * yRand - 2));

						xRand = (std::rand() % 100 + 1) / 100.0f;
						yRand = (std::rand() % 100 + 1) / 100.0f;
						rect2.setPosition(sf::Vector2f(window.getSize().x * xRand - 2, window.getSize().y * yRand - 2));

						dx = rect2.getPosition().x - rect1.getPosition().x;
						dy = rect2.getPosition().y - rect1.getPosition().y;
						distanceText.setString("Distance: " + std::to_string(std::sqrt(dx * dx + dy * dy)));

					}
					break;
			}
		}

		window.clear(sf::Color::White);
		window.draw(rect1);
		window.draw(rect2);
		window.draw(instructionsText);
		window.draw(distanceText);
		window.display();
	}

	return 0;
}