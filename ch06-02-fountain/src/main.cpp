#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Ball.h"

const int NUM_BALLS = 80;
const float GRAVITY = 0.5f;

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Removal", sf::Style::Titlebar | sf::Style::Close, context);
    window.setFramerateLimit(60);

    std::mt19937 mt(time(NULL));
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    std::vector<Ball> balls;

    for (int i = 0; i < NUM_BALLS; i++) {
        sf::Color rndColor;
        rndColor.r = dist(mt) * 255;
        rndColor.g = dist(mt) * 255;
        rndColor.b = dist(mt) * 255;
        Ball ball = Ball(window.getSize().x / 2, window.getSize().y, 2, rndColor);
        ball.id = "ball" + std::to_string(i);
        ball.vx = dist(mt) * 2 - 1;
        //y range (-10,-20)
        ball.vy = dist(mt) * -10 - 10;
        balls.push_back(ball);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        window.clear(sf::Color::White);

        auto ball = balls.begin();
        while (ball != balls.end()) {
            ball->Draw(window, GRAVITY);
            sf::Vector2f ballPos = ball->shape.getPosition();
            if (ballPos.x - ball->shape.getRadius() > window.getSize().x ||
                ballPos.x + ball->shape.getRadius() < 0 ||
                ballPos.y - ball->shape.getRadius() > window.getSize().y ||
                ballPos.y + ball->shape.getRadius() < 0) {
                ball->SetPosition(window.getSize().x / 2, window.getSize().y);
                ball->vx = dist(mt) * 2 - 1;
                ball->vy = dist(mt) * -10 - 10;
            } else
                ++ball;
        }
        window.display();
    }

    return 0;
}