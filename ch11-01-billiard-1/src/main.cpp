#include <iostream>
#include <cmath>
#include "SFML\Graphics.hpp"
#include "Ball.h"
#include "Utils.h"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Billiard 1", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Ball ball0(50 , window.getSize().y / 2, 40, sf::Color::Red);
    ball0.mass = 2;
    ball0.vx = 1;

    Ball ball1(300 , window.getSize().y / 2, 40, sf::Color::Red);
    ball1.mass = 1;
    ball1.vx = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        ball0.Translate(ball0.vx, 0);
        ball1.Translate(ball1.vx, 0);

        float dist = ball1.GetX() - ball0.GetX();
        if(std::abs(dist) < ball0.shape.getRadius() + ball1.shape.getRadius()){
            float vx0Final = ((ball0.mass - ball1.mass) * ball0.vx + 2 * ball1.mass * ball1.vx) / (ball0.mass + ball1.mass);
            float vx1Final = ((ball1.mass - ball0.mass) * ball1.vx + 2 * ball0.mass * ball0.vx) / (ball0.mass + ball1.mass);

            ball0.vx = vx0Final;
            ball1.vx = vx1Final;

            ball0.Translate(ball0.vx, 0);
            ball1.Translate(ball1.vx, 0);
        }

        window.clear(sf::Color::White);
        window.draw(ball0.shape);
        window.draw(ball1.shape);
        window.display();
    }
}