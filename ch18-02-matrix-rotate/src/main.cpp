#include <iostream>
#include <cmath>
#include "SFML\Graphics.hpp"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Matrix Rotate", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    float angle = 0;
    sf::RectangleShape rectangle(sf::Vector2f(150, 150));
    rectangle.setOrigin(75, 75);
    rectangle.setFillColor(sf::Color::Red);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        angle += 0.03f;
        float cos = std::cos(angle),
                sin = std::sin(angle),
                dx = window.getSize().x / 2,
                dy = window.getSize().y / 2;

        sf::Transform transform(cos, -sin, dx, sin, cos, dy, 0, 0, 1);
        window.clear(sf::Color::White);
        window.draw(rectangle, transform);
        window.display();
    }

}
