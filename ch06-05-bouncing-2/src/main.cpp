#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Ball.h"

const float BOUNCE = -0.7f;
const float GRAVITY = 0.1f;

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Bouncing 2", sf::Style::Titlebar | sf::Style::Close, context);
    window.setFramerateLimit(60);

    std::mt19937 mt(time(NULL));
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    Ball ball = Ball(window.getSize().x / 2, window.getSize().y / 2, 30, sf::Color::Red);
    ball.vx = dist(mt) * 10 - 5;
    //y range (-10,-20)
    ball.vy = dist(mt) * 10 - 5;

    float left = 0;
    float right = window.getSize().x;
    float top = 0;
    float bottom = window.getSize().y;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        window.clear(sf::Color::White);

        ball.Draw(window);

        sf::Vector2f ballPos = ball.shape.getPosition();
        ball.vy += GRAVITY;
        if (ballPos.x + ball.shape.getRadius() > right) {
            ball.SetX(right - ball.shape.getRadius());
            ball.vx *= BOUNCE;
        } else if(ballPos.x - ball.shape.getRadius() < left){
            ball.SetX(left + ball.shape.getRadius());
            ball.vx *= BOUNCE;
        }

        if (ballPos.y + ball.shape.getRadius() > bottom) {
            ball.SetY(bottom - ball.shape.getRadius());
            ball.vy *= BOUNCE;
        } else if(ballPos.y - ball.shape.getRadius() < top){
            ball.SetY(top + ball.shape.getRadius());
            ball.vy *= BOUNCE;
        }

        window.display();
    }

    return 0;
}