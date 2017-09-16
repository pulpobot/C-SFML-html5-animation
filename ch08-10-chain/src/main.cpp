#include "SFML\Graphics.hpp"
#include "Ball.h"

const float SPRING = 0.03f;
const float FRICTION = 0.9f;
const float GRAVITY = 2.0f;

void Move(Ball &ball, float targetX, float targetY)
{
    float dx = targetX - ball.GetX();
    float dy = targetY - ball.GetY();
    float ax = dx * SPRING;
    float ay = dy * SPRING;
    ball.vx += ax;
    ball.vy += ay;
    ball.vx *= FRICTION;
    ball.vy *= FRICTION;
    ball.vy += GRAVITY;
    ball.Translate(ball.vx,ball.vy);
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Chain", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Ball ball0(0, 0, 30, sf::Color::Red);
    Ball ball1(0, 0, 30, sf::Color::Red);
    Ball ball2(0, 0, 30, sf::Color::Red);

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

        Move(ball0, mouseX, mouseY);
        Move(ball1, ball0.GetX(), ball0.GetY());
        Move(ball2, ball1.GetX(), ball1.GetY());

        window.clear(sf::Color::White);

        line.clear();
        line.push_back(sf::Vertex(sf::Vector2f(mouseX,mouseY), sf::Color::Black));
        line.push_back(sf::Vertex(sf::Vector2f(ball0.GetX(),ball0.GetY()), sf::Color::Black));
        window.draw(&line[0], line.size(), sf::PrimitiveType::LinesStrip);

        line.clear();
        line.push_back(sf::Vertex(sf::Vector2f(ball0.GetX(),ball0.GetY()), sf::Color::Black));
        line.push_back(sf::Vertex(sf::Vector2f(ball1.GetX(),ball1.GetY()), sf::Color::Black));
        window.draw(&line[0], line.size(), sf::PrimitiveType::LinesStrip);

        line.clear();
        line.push_back(sf::Vertex(sf::Vector2f(ball1.GetX(),ball1.GetY()), sf::Color::Black));
        line.push_back(sf::Vertex(sf::Vector2f(ball2.GetX(),ball2.GetY()), sf::Color::Black));
        window.draw(&line[0], line.size(), sf::PrimitiveType::LinesStrip);

        window.draw(ball0.shape);
        window.draw(ball1.shape);
        window.draw(ball2.shape);

        window.display();
    }
}