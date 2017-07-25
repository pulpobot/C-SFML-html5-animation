#include <SFML/Graphics.hpp>
#include <iostream>

void ColorToGrayscale(sf::Color &color) 
{
	sf::Uint8 y = color.r * 0.2126f + color.g * 0.7152f + color.b * 0.0722f;
	color.r = color.g = color.b = y;
}

int main()
{
	//You can turn off antialiasing if your graphics card doesn't support it
	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(400,400), "Grayscale", sf::Style::Titlebar | sf::Style::Close, context);
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
	sf::Texture texture;
	texture.create(window.getSize().x, window.getSize().y);
	texture.update(window);
	
	//Create an image from the frame captured, so we can modify the pixels
	sf::Image image = texture.copyToImage();

	//pixel iteration
	for (size_t i = 0; i < image.getSize().x; i++)
	{
		for (size_t j = 0; j < image.getSize().y; j++)
		{
			//invert each color component of the pixel: r,g,b,a (0-255)
			colorToUse = image.getPixel(i, j);
			ColorToGrayscale(colorToUse);
			image.setPixel(i,j, colorToUse);
		}
	}

	//store the modified image to a texture
	texture.loadFromImage(image);
	//set a new sprite with the modified texture
	sf::Sprite sprite;
	sprite.setTexture(texture);
		
	//Clear everything and draw the sprite
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