#include <SFML/Graphics.hpp>
#include <cmath>

void ColorMouseConversion(sf::Color &color, int x, int y, sf::Event::MouseMoveEvent mousePos)
{
	int dx = x - mousePos.x,
		dy = y - mousePos.y,
		dist = std::sqrt(dx * dx + dy * dy);

	color.r = std::cos(color.r * dist * 0.001) * 255;
	color.g = std::sin(color.g * dist * 0.001) * 255;
	color.b = std::cos(color.b * dist * 0.0005) * 255;
}

int main()
{
	//You can turn off antialiasing if your graphics card doesn't support it
	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(400,400), "Pixel Move", sf::Style::Titlebar | sf::Style::Close, context);
	window.setFramerateLimit(60);

	window.clear(sf::Color::White);
	sf::Color colorToUse;
	sf::RectangleShape rectangle;

	//draw some stripes: red, green, and blue
	for (size_t i = 0; i < window.getSize().x; i+=10)
	{
		colorToUse = (i % 20 == 0) ? sf::Color::Red : (i % 30 == 0) ? sf::Color::Green : sf::Color::Blue;
		rectangle.setFillColor(colorToUse);
		rectangle.setPosition(i, 0);
		rectangle.setSize(sf::Vector2f(10, window.getSize().y));
		window.draw(rectangle);
	}

	//Capture the current frame info in the window and store it as a texture
	sf::Texture initialStateTexture;
	initialStateTexture.create(window.getSize().x, window.getSize().y);
	initialStateTexture.update(window);
	
	//Create an image from the frame captured, so we can modify the pixels
	sf::Image image = initialStateTexture.copyToImage();

	//store the modified image to a texture
	sf::Texture modifiedStateTexture;
	modifiedStateTexture.create(window.getSize().x, window.getSize().y);
	//set a new sprite with the modified texture
	sf::Sprite sprite;
		
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
				case sf::Event::MouseMoved:
				//Processor Intensive
				image = initialStateTexture.copyToImage();

				//pixel iteration
				for (size_t i = 0; i < image.getSize().x; i++)
				{
					for (size_t j = 0; j < image.getSize().y; j++)
					{
						colorToUse = image.getPixel(i, j);
						ColorMouseConversion(colorToUse, i, j, event.mouseMove);
						image.setPixel(i, j, colorToUse);
					}				
				}

				//store the modified image to a texture
				modifiedStateTexture.loadFromImage(image);
				//set a new sprite with the modified texture
				sprite.setTexture(modifiedStateTexture);
				window.clear(sf::Color::White);
				window.draw(sprite);
				window.display();
			}
		}
	}

	return 0;
}