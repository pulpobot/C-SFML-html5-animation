#include <iostream>
#include <cmath>
#include <random>
#include "SFML\Graphics.hpp"
#include "Ball.h"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Random 3", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 m(std::time(NULL));
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    std::vector<sf::CircleShape> dots;
    int numBalls = 300,
            maxRadius = 50;

    while (numBalls--) {
        float radius = dist(m) * maxRadius,
                angle = dist(m) * (M_PI * 2);
        dots.emplace_back(sf::CircleShape(2));
        dots[dots.size() - 1].setOrigin(2, 2);
        dots[dots.size() - 1].setPosition(window.getSize().x / 2 + std::cos(angle) * radius,
                                          window.getSize().x / 2 + std::sin(angle) * radius);
        dots[dots.size() - 1].setFillColor(sf::Color::Black);
    }

    window.clear(sf::Color::White);

    for (int i = 0; i < dots.size(); ++i) {
        window.draw(dots[i]);
    }

    window.display();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
    }
}