#include "SFML\Graphics.hpp"
#include <iostream>
#include "Ball.h"

const float EASING = 0.05f;

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Easing 1", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Ball ball(0, 0, 30, sf::Color::Red);

    float targetX = window.getSize().x / 2;
    float targetY = window.getSize().y / 2;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        float vx = (targetX - ball.GetX()) * EASING;
        float vy = (targetY - ball.GetY()) * EASING;
        ball.Translate(vx, vy);

        window.clear(sf::Color::White);
        window.draw(ball.shape);
        window.display();
    }
}