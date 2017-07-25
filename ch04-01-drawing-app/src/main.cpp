#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(400,400), "Drawing App", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	//A vector that contains multiple lines
	std::vector<std::vector<sf::Vertex> > lines;

	bool isMousePressed = false;
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
				//Each time we press the mouse button, we start creating a new line
				case sf::Event::MouseButtonPressed:
					isMousePressed = true;
					lines.push_back(std::vector<sf::Vertex>());
					break;
				case sf::Event::MouseButtonReleased:
					isMousePressed = false;
					break;
				case sf::Event::MouseMoved:
					//While the mouse button is being pressed, add a new vertex to the current line with the mouse position
					if (isMousePressed) 
					{
						lines[lines.size()-1].push_back(sf::Vertex(sf::Vector2f(event.mouseMove.x, event.mouseMove.y), sf::Color::Black));
					}
					break;
			}
		}

		window.clear(sf::Color::White);
		//Iterate over each line and draw it as a LinesStrip (independent from each other line)
        std::vector<std::vector<sf::Vertex> >::iterator it;
        for (it = lines.begin(); it != lines.end(); it++)
		{
			if (!(*it).empty())
			{
                //enum doesnt´t create a namespace. Cannot use sf::PrimitiveType::LinesStrip
				window.draw(&((*it)[0]), (*it).size(), sf::LinesStrip);
            }
		}

		window.display();
	}

	return 0;
}