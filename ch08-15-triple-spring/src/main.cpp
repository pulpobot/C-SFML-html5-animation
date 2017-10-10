#include <iostream>
#include <cmath>
#include "SFML\Graphics.hpp"
#include "Ball.h"
#include "Utils.h"

const float SPRING = 0.03f;
const float FRICTION = 0.9f;
const float SPRING_LENGTH = 100;

void SpringTo(Ball &springBall, Ball &targetBall) {
    float dx = springBall.GetX() - targetBall.GetX();
    float dy = springBall.GetY() - targetBall.GetY();
    float angle = std::atan2(dy, dx);
    float targetX = targetBall.GetX() + std::cos(angle) * SPRING_LENGTH;
    float targetY = targetBall.GetY() + std::sin(angle) * SPRING_LENGTH;

    springBall.vx += (targetX - springBall.GetX()) * SPRING;
    springBall.vy += (targetY - springBall.GetY()) * SPRING;
    springBall.vx *= FRICTION;
    springBall.vy *= FRICTION;

    springBall.Translate(springBall.vx, springBall.vy);
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Triple Spring", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Ball ball0((window.getSize().x / 2), (window.getSize().y / 2) - 100, 20, sf::Color::Red);
    Ball ball1((window.getSize().x / 2) - 100, window.getSize().y / 2, 20, sf::Color::Red);
    Ball ball2((window.getSize().x / 2) + 100, window.getSize().y / 2, 20, sf::Color::Red);

    bool ball0_dragging = false;
    bool ball1_dragging = false;
    bool ball2_dragging = false;

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
                case sf::Event::MouseButtonPressed:
                    if (Utils::ContainsPoint(ball0.GetBounds(), mouseX, mouseY))
                        ball0_dragging = true;
                    else if (Utils::ContainsPoint(ball1.GetBounds(), mouseX, mouseY))
                        ball1_dragging = true;
                    else if (Utils::ContainsPoint(ball2.GetBounds(), mouseX, mouseY))
                        ball2_dragging = true;
                    break;
                case sf::Event::MouseButtonReleased:
                    ball0_dragging = false;
                    ball1_dragging = false;
                    ball2_dragging = false;
                case sf::Event::MouseMoved:
                    mouseX = event.mouseMove.x;
                    mouseY = event.mouseMove.y;
                    if (ball0_dragging) {
                        ball0.SetX(mouseX);
                        ball0.SetY(mouseY);
                    } else if (ball1_dragging) {
                        ball1.SetX(mouseX);
                        ball1.SetY(mouseY);
                    } else if (ball2_dragging) {
                        ball2.SetX(mouseX);
                        ball2.SetY(mouseY);
                    }
                    break;
            }
        }

        if (!ball0_dragging) {
            SpringTo(ball0, ball1);
            SpringTo(ball0, ball2);
        }
        if (!ball1_dragging) {
            SpringTo(ball1, ball0);
            SpringTo(ball1, ball2);
        }
        if (!ball2_dragging) {
            SpringTo(ball2, ball0);
            SpringTo(ball2, ball1);
        }

        window.clear(sf::Color::White);
        line.clear();
        line.emplace_back(sf::Vertex(sf::Vector2f(ball0.GetX(), ball0.GetY()), sf::Color::Black));
        line.emplace_back(sf::Vertex(sf::Vector2f(ball1.GetX(), ball1.GetY()), sf::Color::Black));
        line.emplace_back(sf::Vertex(sf::Vector2f(ball2.GetX(), ball2.GetY()), sf::Color::Black));
        line.emplace_back(sf::Vertex(sf::Vector2f(ball0.GetX(), ball0.GetY()), sf::Color::Black));
        window.draw(&line[0], line.size(), sf::PrimitiveType::LinesStrip);

        window.draw(ball0.shape);
        window.draw(ball1.shape);
        window.draw(ball2.shape);

        window.display();
    }
}