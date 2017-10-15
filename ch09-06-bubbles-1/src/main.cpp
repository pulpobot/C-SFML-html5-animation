#include <iostream>
#include <cmath>
#include <random>
#include "SFML\Graphics.hpp"
#include "Ball.h"

const float SPRING = 0.3f;
const float BOUNCE = -1;

void Move(Ball &ball, sf::RenderWindow &window) {
    ball.Translate(ball.vx, ball.vy);

    if (ball.GetX() + ball.shape.getRadius() > window.getSize().x) {
        ball.SetX(window.getSize().x - ball.shape.getRadius());
        ball.vx *= BOUNCE;
    } else if (ball.GetX() - ball.shape.getRadius() < 0) {
        ball.SetX(ball.shape.getRadius());
        ball.vx *= BOUNCE;
    }

    if (ball.GetY() + ball.shape.getRadius() > window.getSize().y) {
        ball.SetY(window.getSize().y - ball.shape.getRadius());
        ball.vy *= BOUNCE;
    } else if (ball.GetY() - ball.shape.getRadius() < 0) {
        ball.SetY(ball.shape.getRadius());
        ball.vy *= BOUNCE;
    }
}

void Draw(Ball &centerBall, Ball &ball, sf::RenderWindow &window) {
    float dx = ball.GetX() - centerBall.GetX();
    float dy = ball.GetY() - centerBall.GetY();
    float dist = std::sqrt(dx * dx + dy * dy);
    float minDis = ball.shape.getRadius() + centerBall.shape.getRadius();

    if (dist < minDis) {
        float angle = std::atan2(dy, dx);
        float tx = centerBall.GetX() + std::cos(angle) * minDis;
        float ty = centerBall.GetY() + std::sin(angle) * minDis;
        ball.vx += (tx - ball.GetX()) * SPRING;
        ball.vy += (ty - ball.GetY()) * SPRING;
    }

    window.draw(ball.shape);
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Bubbles 1", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 mt(std::time(NULL));
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    Ball centerBall(window.getSize().x / 2, window.getSize().y / 2, 100, sf::Color(204, 204, 204, 255)); //#cccccc

    std::vector<Ball> balls;
    int numBalls = 10;

    for (int i = 0; i < numBalls; ++i) {
        balls.emplace_back(Ball(dist(mt) * window.getSize().x / 2, dist(mt) * window.getSize().y / 2, dist(mt) * 40 + 5,
                                sf::Color(dist(mt) * 255, dist(mt) * 255, dist(mt) * 255, 255)));
        balls[i].vx = dist(mt) * 6 - 3;
        balls[i].vy = dist(mt) * 6 - 3;
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
        for (int i = 0; i < numBalls; ++i) {
            Move(balls[i], window);
            Draw(centerBall, balls[i], window);
        }

        window.draw(centerBall.shape);

        window.display();
    }
}