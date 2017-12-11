#include <iostream>
#include <cmath>
#include "SFML\Graphics.hpp"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Skew XY", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    float angle = 0;
    sf::RectangleShape rectangle(sf::Vector2f(150, 150));
    rectangle.setOrigin(75, 75);
    rectangle.setFillColor(sf::Color::Red);

    float skewX = 0,
            skewY = 0,
            dx = window.getSize().x / 2,
            dy = window.getSize().y / 2;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    skewX = (event.mouseMove.x - (window.getSize().x / 2.0f)) * 0.01f;
                    skewY = (event.mouseMove.y - (window.getSize().y / 2.0f)) * 0.01f;
            }
        }

        sf::Transform transform = sf::Transform(1, skewX, dx, skewY, 1, dy, 0, 0, 1);

        window.clear(sf::Color::White);
        window.draw(rectangle, transform);
        window.display();
    }

}
