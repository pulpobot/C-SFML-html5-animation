#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ball.h"

const float FRICTION = 0.95f;

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Friction 2", sf::Style::Titlebar | sf::Style::Close, context);
    window.setFramerateLimit(60);

    std::mt19937 mt(time(NULL));
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    Ball ball = Ball(window.getSize().x / 2, window.getSize().y / 2, 30, sf::Color::Red);
    ball.vx = dist(mt) * 10 - 5;
    //y range (-10,-20)
    ball.vy = dist(mt) * 10 - 5;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        ball.vy *= FRICTION;
        ball.vx *= FRICTION;

        window.clear(sf::Color::White);
        ball.Draw(window);
        window.display();
    }

    return 0;
}