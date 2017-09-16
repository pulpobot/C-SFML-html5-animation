#include "SFML\Graphics.hpp"
#include "Ball.h"

const float SPRING = 0.03f;
const float FRICTION = 0.95f;

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Spring 4", sf::Style::Titlebar | sf::Style::Close,
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
                case sf::Event::MouseMoved:
                    targetX = event.mouseMove.x;
                    targetY = event.mouseMove.y;
                    break;
            }
        }

        float dx = targetX - ball.GetX();
        float dy = targetY - ball.GetY();
        float ax = dx * SPRING;
        float ay = dy * SPRING;
        ball.vx += ax;
        ball.vy += ay;
        ball.vx *= FRICTION;
        ball.vy *= FRICTION;

        window.clear(sf::Color::White);
        ball.Draw(window);
        window.display();
    }
}