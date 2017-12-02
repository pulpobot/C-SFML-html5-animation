#include <iostream>
#include <random>
#include <algorithm>
#include "SFML\Graphics.hpp"
#include "ball3d.h"

float fl = 250,
        vpX = 0,
        vpY = 0,
        top = -200,
        bottom = 200,
        left = -200,
        right = 200,
        front = -200,
        back = 200;

int numBalls = 20;
std::vector<Ball3d> balls;

void Move(Ball3d &ball) {
    ball.xPos += ball.vx;
    ball.yPos += ball.vy;
    ball.zPos += ball.vz;

    //check boundaries
    if (ball.xPos + ball.shape.getRadius() > right) {
        ball.xPos = right - ball.shape.getRadius();
        ball.vx *= -1;
    } else if (ball.xPos - ball.shape.getRadius() < left) {
        ball.xPos = left + ball.shape.getRadius();
        ball.vx *= -1;
    }
    if (ball.yPos + ball.shape.getRadius() > bottom) {
        ball.yPos = bottom - ball.shape.getRadius();
        ball.vy *= -1;
    } else if (ball.yPos - ball.shape.getRadius() < top) {
        ball.yPos = top + ball.shape.getRadius();
        ball.vy *= -1;
    }
    if (ball.zPos + ball.shape.getRadius() > back) {
        ball.zPos = back - ball.shape.getRadius();
        ball.vz *= -1;
    } else if (ball.zPos - ball.shape.getRadius() < front) {
        ball.zPos = front + ball.shape.getRadius();
        ball.vz *= -1;
    }

    if (ball.zPos > -fl) {
        float scale = fl / (fl + ball.zPos);
        ball.shape.setScale(sf::Vector2f(scale, scale));
        ball.SetX(vpX + ball.xPos * scale);
        ball.SetY(vpY + ball.yPos * scale);
        ball.visible = true;
    } else
        ball.visible = false;
}

void CheckCollision(Ball3d &ballA, int i) {
    for (int j = i + 1; j < numBalls; ++j) {
        Ball3d ballB = balls[j];
        float dx = ballA.xPos - ballB.xPos;
        float dy = ballA.yPos - ballB.yPos;
        float dz = ballA.zPos - ballB.zPos;

        float dist = std::sqrt(dx * dx + dy * dy + dz * dz);

        if (dist < ballA.shape.getRadius() + ballB.shape.getRadius()) {
            ballA.shape.setFillColor(sf::Color::Blue);
            ballB.shape.setFillColor(sf::Color::Blue);
        }
    }
}

bool zSort(const Ball3d &ballA, const Ball3d &ballB) {
    return ballB.zPos < ballA.zPos;
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Collision 3D", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 m(time(NULL));
    std::uniform_real_distribution<float> t(0.0f, 1.0f);
    vpX = window.getSize().x / 2.0f;
    vpY = window.getSize().y / 2.0f;

    for (int i = 0; i < numBalls; ++i) {
        balls.emplace_back(Ball3d(0, 0, 0, 15, sf::Color::Red));
        balls[i].xPos = t(m) * 400 - 200;
        balls[i].yPos = t(m) * 400 - 200;
        balls[i].zPos = t(m) * 400 - 200;
        balls[i].vx = t(m) * 5 - 1;
        balls[i].vy = t(m) * 5 - 1;
        balls[i].vz = t(m) * 5 - 1;
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

        for (int i = 0; i < numBalls; ++i) {
            Move(balls[i]);
        }

        for (int i = 0; i < numBalls; ++i) {
            CheckCollision(balls[i], i);
        }

        std::sort(balls.begin(), balls.end(), zSort);

        window.clear(sf::Color::White);
        for (int i = 0; i < numBalls; ++i) {
            balls[i].Draw(window);
        }
        window.display();
    }

}
