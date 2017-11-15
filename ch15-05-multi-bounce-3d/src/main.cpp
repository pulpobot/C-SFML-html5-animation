#include <iostream>
#include <random>
#include "SFML\Graphics.hpp"
#include "Ball3d.h"

float  fl = 250,
        top = -100,
        bottom = 100,
        left = -100,
        right = 100,
        front = -100,
        back = 100,
        vpX = 0,
        vpY = 0;

void Move(Ball3d &ball){
    ball.xPos += ball.vx;
    ball.yPos += ball.vy;
    ball.zPos += ball.vz;

    //check boundaries
    if(ball.xPos + ball.shape.getRadius() > right){
        ball.xPos = right - ball.shape.getRadius();
        ball.vx *= -1;
    } else if(ball.xPos - ball.shape.getRadius() < left){
        ball.xPos = left + ball.shape.getRadius();
        ball.vx *= -1;
    }

    if(ball.yPos + ball.shape.getRadius() > bottom){
        ball.yPos = bottom - ball.shape.getRadius();
        ball.vy *= -1;
    } else if(ball.yPos - ball.shape.getRadius() < top){
        ball.yPos = top + ball.shape.getRadius();
        ball.vy *= -1;
    }

    if(ball.zPos + ball.shape.getRadius() > back){
        ball.zPos = back - ball.shape.getRadius();
        ball.vz *= -1;
    } else if(ball.zPos - ball.shape.getRadius() < front){
        ball.zPos = front + ball.shape.getRadius();
        ball.vz *= -1;
    }

    if (ball.zPos > -fl) {
        float scale = fl / (fl + ball.zPos);
        ball.shape.setScale(scale, scale);
        ball.SetPosition(vpX + ball.xPos * scale, vpY + ball.yPos * scale, ball.zPos);
        ball.visible = true;
    }else
        ball.visible = false;
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Multi Bounce 3D", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 m(time(NULL));
    std::uniform_real_distribution<float> t(0.0f, 1.0f);

    std::vector<Ball3d> balls = std::vector<Ball3d>();
    int numBall = 50;

    for (int i = 0; i < numBall; ++i) {
        balls.emplace_back(Ball3d(0, 0, 0, 15, sf::Color::Red));
        balls[i].vx = t(m) * 10 - 5;
        balls[i].vy = t(m) * 10 - 5;
        balls[i].vz = t(m) * 10 - 5;
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

        window.clear(sf::Color::White);

        for (int i = 0; i < balls.size(); ++i) {
            Move(balls[i]);
            balls[i].Draw(window);
        }

        window.display();
    }

}
