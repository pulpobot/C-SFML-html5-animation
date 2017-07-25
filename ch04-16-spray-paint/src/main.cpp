#include <SFML/Graphics.hpp>
#include <cmath>

//Max size of the brush to paint
const int BRUSH_SIZE = 25;
//Amount of points per spray
const int BRUSH_DENSITY = 75;
//PI Value
#define PI_Int 314159265
#define PI 3.14159265
#define clip(n, lower, upper) if (n < lower) n= lower; else if (n > upper) n= upper


int main()
{
	//You can turn off antialiasing if your graphics card doesn't support it
	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(400,400), "Spray Paint", sf::Style::Titlebar | sf::Style::Close, context);
	window.setFramerateLimit(60);

	sf::Color colorToUse;

	//Create a texture with a size equal to the window
	sf::Texture texture;
	texture.create(window.getSize().x, window.getSize().y);
	
	//Create an image, so we can modify the pixels
	sf::Image image = texture.copyToImage();	
	//set a new sprite with the modified texture that is going to be displayed
	sf::Sprite sprite;
		
	window.clear(sf::Color::White);
	window.display();

	float angle;
	float brushSize;
	float rndRadius;
	float xpos;
	float ypos;
	sf::Color brushColor = sf::Color::Red;
	//Set the seed
	std::srand(time(NULL));
	bool mousePressed = false;
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
				case sf::Event::MouseButtonPressed:
					brushColor = sf::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255);
					mousePressed = true;
					break;
				case sf::Event::MouseButtonReleased:
					mousePressed = false;
					break;
				case sf::Event::MouseMoved:
					if (mousePressed)
					{
						
						//loop over each brush point
						for (size_t i = 0; i < BRUSH_DENSITY; i++)
						{	
							//set a random angle and radius for this point
							angle = std::rand() % (PI_Int * 2);
							angle /= 100;
							rndRadius = std::rand() % BRUSH_SIZE;
							//calculate its position inside the brush
							xpos = (event.mouseMove.x + std::cos(angle * PI / 180.0) * rndRadius);
							//clamp it, so it doesn't go beyond window boundaries
							clip(xpos, 0, window.getSize().x-1);
							ypos = (event.mouseMove.y + std::sin(angle * PI / 180.0) * rndRadius); //remove decimal;
							//clamp it, so it doesn't go beyond window boundaries
							clip(ypos, 0, window.getSize().y-1);

							image.setPixel(xpos, ypos, brushColor);

							//Another method, by drawing circle shapes
							/*sf::CircleShape shape;
							shape.setPosition(xpos, ypos);
							shape.setFillColor(brushColor);
							shape.setRadius(1);
							window.draw(shape);*/
						}
						//store the modified image to a texture
						texture.loadFromImage(image);
						//set a new sprite with the modified texture
						sprite.setTexture(texture);

						window.clear(sf::Color::White);
						window.draw(sprite);
						window.display();
					}
				break;
			}
		}
	}

	return 0;
}