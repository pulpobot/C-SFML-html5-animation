#include <iostream>
#include <cmath>
#include <random>
#include "SFML\Graphics.hpp"
#include "Ball.h"

const float BOUNCE = -1.0f;

sf::Vector2f Rotate(float x, float y, float sin, float cos, bool reverse) {
    sf::Vector2f result;
    result.x = (reverse) ? (x * cos + y * sin) : (x * cos - y * sin);
    result.y = (reverse) ? (y * cos - x * sin) : (y * cos + x * sin);
    return result;
}

void CheckCollision(Ball &ball0, Ball &ball1) {
    float dx = ball1.GetX() - ball0.GetX();
    float dy = ball1.GetY() - ball0.GetY();
    float dist = std::sqrt(dx * dx + dy * dy);

    if (dist < ball0.shape.getRadius() + ball1.shape.getRadius()) {
        //calculate angle, sine, and cosine
        float angle = std::atan2(dy, dx);
        float sin = std::sin(angle);
        float cos = std::cos(angle);

        //rotate ball0's position
        sf::Vector2f pos0(0, 0);

        //rotate balls1's position
        sf::Vector2f pos1(Rotate(dx, dy, sin, cos, true));

        //rotate ball0's velocity
        sf::Vector2f vel0(Rotate(ball0.vx, ball0.vy, sin, cos, true));

        //rotate ball1's velocity
        sf::Vector2f vel1(Rotate(ball1.vx, ball1.vy, sin, cos, true));

        //collision reaction
        float vxTotal = vel0.x - vel1.x;
        vel0.x = ((ball0.mass - ball1.mass) * vel0.x + 2 * ball1.mass * vel1.x) / (ball0.mass + ball1.mass);
        vel1.x = vxTotal + vel0.x;

        //update position
        pos0.x += vel0.x;
        pos1.x += vel1.x;

        //rotate positions back
        sf::Vector2f pos0F(Rotate(pos0.x, pos0.y, sin, cos, false));
        sf::Vector2f pos1F(Rotate(pos1.x, pos1.y, sin, cos, false));

        //adjust positions to actual screen position
        ball1.SetX(ball0.GetX() + pos1F.x);
        ball1.SetY(ball0.GetY() + pos1F.y);
        ball0.SetX(ball0.GetX() + pos0F.x);
        ball0.SetY(ball0.GetY() + pos0F.y);

        //rotate velocities back
        sf::Vector2f vel0F(Rotate(vel0.x, vel0.y, sin, cos, false));
        sf::Vector2f vel1F(Rotate(vel1.x, vel1.y, sin, cos, false));

        ball0.vx = vel0F.x;
        ball0.vy = vel0F.y;
        ball1.vx = vel1F.x;
        ball1.vy = vel1F.y;
    }
}

void CheckWalls(Ball &ball, sf::RenderWindow &window) {
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

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Billiard 4", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 m(std::time(NULL));
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    Ball ball0(window.getSize().x - 200, window.getSize().y - 200, 80, sf::Color::Red);
    ball0.mass = 2;
    ball0.vx = dist(m) * 10 - 5;
    ball0.vy = dist(m) * 10 - 5;

    Ball ball1(100, 100, 40, sf::Color::Red);
    ball1.mass = 1;
    ball1.vx = dist(m) * 10 - 5;
    ball1.vy = dist(m) * 10 - 5;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        ball0.Translate(ball0.vx, ball0.vy);
        ball1.Translate(ball1.vx, ball1.vy);

        CheckCollision(ball0, ball1);
        CheckWalls(ball0, window);
        CheckWalls(ball1, window);

        window.clear(sf::Color::White);
        window.draw(ball0.shape);
        window.draw(ball1.shape);
        window.display();
    }
}