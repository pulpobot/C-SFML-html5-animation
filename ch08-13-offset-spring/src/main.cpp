#include <iostream>
#include <cmath>
#include "SFML\Graphics.hpp"
#include "Ball.h"

const float SPRING = 0.03f;
const float FRICTION = 0.9f;
const float SPRING_LENGTH = 100;

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Offset Spring", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Ball ball(window.getSize().x / 2, window.getSize().y / 2, 40, sf::Color::Red);

    float mouseX = window.getSize().x / 2;
    float mouseY = window.getSize().y / 2;
    std::vector<sf::Vertex> line;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    mouseX = event.mouseMove.x;
                    mouseY = event.mouseMove.y;
                    break;
            }
        }

        window.clear(sf::Color::White);

        float dx = ball.GetX() - mouseX;
        float dy = ball.GetY() - mouseY;
        float angle = std::atan2(dy,dx);
        float targetX = mouseX + std::cos(angle) * SPRING_LENGTH;
        float targetY = mouseY + std::sin(angle) * SPRING_LENGTH;

        ball.vx += (targetX - ball.GetX()) * SPRING;
        ball.vy += (targetY - ball.GetY()) * SPRING;
        ball.vx *= FRICTION;
        ball.vy *= FRICTION;
        ball.Translate(ball.vx, ball.vy);

        line.clear();
        line.emplace_back(sf::Vertex(sf::Vector2f(ball.GetX(), ball.GetY()), sf::Color::Black));
        line.emplace_back(sf::Vertex(sf::Vector2f(mouseX, mouseY), sf::Color::Black));
        window.draw(&line[0], line.size(), sf::PrimitiveType::LinesStrip);
        window.draw(ball.shape);

        window.display();
    }
}