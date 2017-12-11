#include <iostream>
#include <cmath>
#include <random>
#include "SFML\Graphics.hpp"
#include "Ball.h"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Brownian 1", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 m(std::time(NULL));
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    std::vector<Ball> dots;
    int numBalls = 50;
    float friction = 0.95f;

    for (int i = 0; i < numBalls; ++i) {
        dots.emplace_back(Ball(dist(m) * window.getSize().x, dist(m) * window.getSize().x, 2, sf::Color::Black));
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

        for (int i = 0; i < dots.size(); ++i) {
            dots[i].vx += dist(m) * 0.2f - 0.1f;
            dots[i].vy += dist(m) * 0.2f - 0.1f;
            dots[i].Translate(dots[i].vx, dots[i].vy);
            dots[i].vx *= friction;
            dots[i].vy *= friction;

            if (dots[i].GetX() > window.getSize().x) {
                dots[i].SetX(0);
            } else if (dots[i].GetX() < 0) {
                dots[i].SetX(window.getSize().x);
            }
            if (dots[i].GetY() > window.getSize().y) {
                dots[i].SetY(0);
            } else if (dots[i].GetY() < 0) {
                dots[i].SetY(window.getSize().y);
            }

            window.draw(dots[i].shape);
        }

        window.display();
    }
}