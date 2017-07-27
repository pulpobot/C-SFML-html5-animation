#include <SFML/Graphics.hpp>
#include <cmath>
#include "Ship.h"

#define PI 3.14159265
const float THRUST_FORCE = 0.05f;

int main()
{
	//You can turn off antialiasing if your graphics card doesn't support it
	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(400,400), "Ship Sim 2", sf::Style::Titlebar | sf::Style::Close, context);
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
		float left = 0;
		float right = window.getSize().x;
		float top = 0;
		float bottom = window.getSize().y;

		vx += ax;
		vy += ay;
		ship.Translate(vx, vy);
		sf::FloatRect shipBounds = ship.shape.getLocalBounds();
		if(ship.GetX() - shipBounds.width / 2 > right){
			ship.SetX(left - shipBounds.width / 2);
		}else if(ship.GetX() + shipBounds.width/ 2 < left){
			ship.SetX(right + shipBounds.width / 2);
		}

		if(ship.GetY() - shipBounds.height / 2 > bottom){
			ship.SetY(top - shipBounds.height / 2);
		}else if(ship.GetY() < top - shipBounds.height / 2){
			ship.SetY(bottom + shipBounds.height / 2);
		}

		window.clear(sf::Color::Black);
		ship.Draw(&window);
		window.display();

	}

	return 0;
}