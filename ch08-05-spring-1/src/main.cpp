#include "SFML\Graphics.hpp"
#include "Ball.h"

const float SPRING = 0.03f;

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Spring 1", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Ball ball(0, window.getSize().y / 2, 30, sf::Color::Red);

    float targetX = window.getSize().x / 2;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        float dx = targetX - ball.GetX();
        float ax = dx * SPRING;
        ball.vx += ax;

        window.clear(sf::Color::White);
        ball.Draw(window);
        window.display();
    }
}