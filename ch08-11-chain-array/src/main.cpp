#include <iostream>
#include "SFML\Graphics.hpp"
#include "Ball.h"

const float SPRING = 0.03f;
const float FRICTION = 0.9f;
const float GRAVITY = 2.0f;

void Move(Ball &ball, float targetX, float targetY) {
    float dx = targetX - ball.GetX();
    float dy = targetY - ball.GetY();
    float ax = dx * SPRING;
    float ay = dy * SPRING;
    ball.vx += ax;
    ball.vy += ay;
    ball.vx *= FRICTION;
    ball.vy *= FRICTION;
    ball.vy += GRAVITY;
    ball.Translate(ball.vx, ball.vy);
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Chain Array", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::vector<Ball> balls;
    int numBalls = 5;

    for (int i = 0; i < numBalls; ++i) {
        balls.emplace_back(0, 0, 20, sf::Color::Red);
    }

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
        for (int i = 0; i < balls.size(); ++i) {
            if (i == 0)
                Move(balls[i], mouseX, mouseY);
            else
                Move(balls[i], balls[i - 1].GetX(), balls[i - 1].GetY());
        }

        for (int i = 0; i < balls.size(); ++i) {
            line.clear();
            if (i == 0) {
                line.emplace_back(sf::Vector2f(mouseX, mouseY), sf::Color::Black);
                line.emplace_back(sf::Vertex(sf::Vector2f(balls[i].GetX(), balls[i].GetY()), sf::Color::Black));
            } else {
                line.emplace_back(sf::Vertex(sf::Vector2f(balls[i-1].GetX(), balls[i-1].GetY()), sf::Color::Black));
                line.emplace_back(sf::Vertex(sf::Vector2f(balls[i].GetX(), balls[i].GetY()), sf::Color::Black));
            }
            window.draw(&line[0], line.size(), sf::PrimitiveType::LinesStrip);

            window.draw(balls[i].shape);
        }

        window.display();
    }
}