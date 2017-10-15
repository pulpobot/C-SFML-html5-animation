#include <iostream>
#include <cmath>
#include "SFML\Graphics.hpp"
#include "Ball.h"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Rotate 1", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Ball ball(0, 0, 40, sf::Color::Red);
    float vr = 0.05f;
    float angle = 0;
    float radius = 150;
    float centerX = window.getSize().x / 2;
    float centerY = window.getSize().y / 2;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        ball.SetX(centerX + std::cos(angle) * radius);
        ball.SetY(centerY + std::sin(angle) * radius);
        angle += vr;

        window.clear(sf::Color::White);
        window.draw(ball.shape);
        window.display();
    }
}