#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	//You can turn off antialiasing if your graphics card doesn't support it
	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(400,400), "Invert Color", sf::Style::Titlebar | sf::Style::Close, context);
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
			image.setPixel(i,j, sf::Color(255-colorToUse.r, 255 - colorToUse.g, 255 - colorToUse.b));
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