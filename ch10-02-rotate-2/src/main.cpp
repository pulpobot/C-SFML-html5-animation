#include <iostream>
#include <cmath>
#include <random>
#include "SFML\Graphics.hpp"
#include "Ball.h"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Rotate 2", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 mt(time(NULL));
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    float vr = 0.05f;
    float cos = std::cos(vr);
    float sin = std::sin(vr);
    float centerX = window.getSize().x / 2;
    float centerY = window.getSize().y / 2;

    Ball ball(dist(mt) * window.getSize().x, dist(mt) * window.getSize().y, 40, sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        float x1 = ball.GetX() - centerX;
        float y1 = ball.GetY() - centerY;
        float x2 = cos * x1 - sin * y1;
        float y2 = cos * y1 + sin * x1;

        ball.SetX(centerX + x2);
        ball.SetY(centerY + y2);

        window.clear(sf::Color::White);
        window.draw(ball.shape);
        window.display();
    }
}