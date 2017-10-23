#include <iostream>
#include <cmath>
#include <random>
#include "SFML\Graphics.hpp"
#include "Ball.h"

const float BOUNCE = -1.0f;

void CheckCollision(Ball &ball0, Ball &ball1){
    float dx = ball1.GetX() - ball0.GetX();
    float dy = ball1.GetY() - ball0.GetY();
    float dist = std::sqrt(dx * dx + dy * dy);

    if(dist < ball0.shape.getRadius() + ball1.shape.getRadius()){
        //calculate angle, sine, and cosine
        float angle = std::atan2(dy, dx);
        float sin = std::sin(angle);
        float cos = std::cos(angle);

        //rotate ball0's position
        float x0 = 0;
        float y0 = 0;

        //rotate balls1's position
        float x1 = dx * cos + dy * sin;
        float y1 = dy * cos - dx * sin;

        //rotate ball0's velocity
        float vx0 = ball0.vx * cos + ball0.vy * sin;
        float vy0 = ball0.vy * cos - ball0.vx * sin;

        //rotate ball1's velocity
        float vx1 = ball1.vx * cos + ball1.vy * sin;
        float vy1 = ball1.vy * cos - ball1.vx * sin;

        //collision reaction
        float vxTotal = vx0 - vx1;
        vx0 = ((ball0.mass - ball1.mass) * vx0 + 2 * ball1.mass * vx1) / (ball0.mass + ball1.mass);
        vx1 = vxTotal + vx0;
        x0 += vx0;
        x1 += vx1;

        //rotate positions back
        float x0Final = x0 * cos - y0 * sin;
        float y0Final = y0 * cos + x0 * sin;
        float x1Final = x1 * cos - y1 * sin;
        float y1Final = y1 * cos + x1 * sin;

        //adjust positions to actual screen position
        ball1.SetX(ball0.GetX() + x1Final);
        ball1.SetY(ball0.GetY() + y1Final);
        ball0.SetX(ball0.GetX() + x0Final);
        ball0.SetY(ball0.GetY() + y0Final);

        //rotate velocities back
        ball0.vx = vx0 * cos - vy0 * sin;
        ball0.vy = vy0 * cos + vx0 * sin;
        ball1.vx = vx1 * cos - vy1 * sin;
        ball1.vy = vy1 * cos + vx1 * sin;
    }
}

void CheckWalls(Ball &ball, sf::RenderWindow &window){
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

    sf::RenderWindow window(sf::VideoMode(400, 400), "Billiard 3", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 m(std::time(NULL));
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    Ball ball0(window.getSize().x - 200 , window.getSize().y - 200, 80, sf::Color::Red);
    ball0.mass = 2;
    ball0.vx = dist(m) * 10 - 5;
    ball0.vy = dist(m) * 10 - 5;

    Ball ball1(100 ,100, 40, sf::Color::Red);
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