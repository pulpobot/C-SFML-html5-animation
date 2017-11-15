#include <iostream>
#include <random>
#include <algorithm>
#include "SFML\Graphics.hpp"
#include "Ball3d.h"

float fl = 250,
        floorBounds = 200,
        vpX = 0,
        vpY = 0,
        gravity = 0.2f,
        bounce = -0.6f;

void Move(Ball3d &ball) {
    ball.vy += gravity;

    ball.xPos += ball.vx;
    ball.yPos += ball.vy;
    ball.zPos += ball.vz;

    //check boundaries
    if (ball.yPos > floorBounds) {
        ball.yPos = floorBounds;
        ball.vy *= bounce;
    }

    if (ball.zPos > -fl) {
        float scale = fl / (fl + ball.zPos);
        ball.shape.setScale(scale, scale);
        ball.SetPosition(vpX + ball.xPos * scale, vpY + ball.yPos * scale, ball.zPos);
        ball.visible = true;
    } else
        ball.visible = false;
}

bool zSort(const Ball3d &ballA, const Ball3d &ballB) {
    return ballB.zPos < ballA.zPos;
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Bouncy Balls", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 m(time(NULL));
    std::uniform_real_distribution<float> t(0.0f, 1.0f);

    std::vector<Ball3d> balls = std::vector<Ball3d>();
    int numBall = 100;

    for (int i = 0; i < numBall; ++i) {
        balls.emplace_back(Ball3d(0, 0, 0, 3, sf::Color(t(m) * 255, t(m) * 255, t(m) * 255, 255)));
        balls[i].yPos = -100;
        balls[i].vx = t(m) * 6 - 3;
        balls[i].vy = t(m) * 6 - 3;
        balls[i].vz = t(m) * 6 - 3;
    }

    vpX = window.getSize().x / 2.0f;
    vpY = window.getSize().y / 2.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        window.clear(sf::Color::Black);
        for (int i = 0; i < balls.size(); ++i) {
            Move(balls[i]);
        }
        std::sort(balls.begin(), balls.end(), zSort);

        for (int i = 0; i < balls.size(); ++i) {
            balls[i].Draw(window);
        }

        window.display();
    }

}
