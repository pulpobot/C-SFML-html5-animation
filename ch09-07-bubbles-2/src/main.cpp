#include <iostream>
#include <cmath>
#include <random>
#include "SFML\Graphics.hpp"
#include "Ball.h"

const float SPRING = 0.3f;
const float BOUNCE = -0.5;
const float GRAVITY = 0.1;

void Move(Ball &ball, sf::RenderWindow &window) {
    ball.vy += GRAVITY;
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

void CheckCollision(std::vector<Ball> &balls, int i, sf::RenderWindow &window) {
    for (int j = i + 1; j < balls.size(); ++j) {
        float dx = balls[j].GetX() - balls[i].GetX();
        float dy = balls[j].GetY() - balls[i].GetY();
        float dist = std::sqrt(dx * dx + dy * dy);
        float minDis = balls[i].shape.getRadius() + balls[j].shape.getRadius();

        if (dist < minDis) {
            float angle = std::atan2(dy, dx);
            float tx = balls[i].GetX() + std::cos(angle) * minDis;
            float ty = balls[i].GetY() + std::sin(angle) * minDis;
            float ax = (tx - balls[j].GetX()) * SPRING * 0.5f;
            float ay = (ty - balls[j].GetY()) * SPRING * 0.5f;
            balls[i].vx -= ax;
            balls[i].vy -= ay;
            balls[j].vx += ax;
            balls[j].vy += ay;
        }
    }

    window.draw(balls[i].shape);
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Bubbles 2", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 mt(std::time(NULL));
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    std::vector<Ball> balls;
    int numBalls = 10;

    for (int i = 0; i < numBalls; ++i) {
        balls.emplace_back(Ball(dist(mt) * window.getSize().x / 2, dist(mt) * window.getSize().y / 2, dist(mt) * 30 + 20,
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
            CheckCollision(balls, i, window);
        }

        window.display();
    }
}