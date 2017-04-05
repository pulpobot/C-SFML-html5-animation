#include <SFML/Graphics.hpp>
#include "Ship.h"

#define PI 3.14159265
const float THRUST_FORCE = 0.05f;

int main()
{
	//You can turn off antialiasing if your graphics card doesn't support it
	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(400,400), "Ship Sim", sf::Style::Titlebar | sf::Style::Close, context);
	window.setFramerateLimit(60);
	
	Ship ship = Ship(window.getSize().x / 2, window.getSize().y / 2);

	float vr = 0.0f;
	float vx = 0.0f;
	float vy = 0.0f;
	float thrust = 0;

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
						case sf::Keyboard::Up:
							ship.showFlame = true;
							thrust = THRUST_FORCE;
							break;
						case sf::Keyboard::Left:
							vr = -3.0f;
							break;
						case sf::Keyboard::Right:
							vr = 3.0f;
							break;
					}
					break;
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						ship.showFlame = false;
						thrust = 0.0f;
						break;
					case sf::Keyboard::Left:
						vr = 0.0f;
						break;
					case sf::Keyboard::Right:
						vr = 0.0f;
						break;
					}
			}
		}

		ship.Rotate(vr);

		float ax = std::cos(ship.GetRotation() * PI / 180.0f) * thrust;
		float ay = std::sin(ship.GetRotation() * PI / 180.0f) * thrust;
		vx += ax;
		vy += ay;
		ship.Translate(vx, vy);
		
		window.clear(sf::Color::Black);
		ship.Draw(&window);
		window.display();

	}

	return 0;
}