#include <iostream>
#include <cmath>
#include <random>
#include "SFML\Graphics.hpp"
#include "Ball.h"
#include "Utils.h"

float fps = 30;

void DrawFrame(Ball &ball, sf::RenderWindow &window){
    ball.Translate(ball.vx, 0);
    window.clear(sf::Color::White);
    window.draw(ball.shape);
    window.display();
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Timer", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 m(std::time(NULL));
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    Ball ball(0, window.getSize().y / 2, 40, sf::Color::Red);
    ball.vx = 5;
    Utils::Timer t ;
    t.callback = &DrawFrame;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        t.Execute(fps, ball, window);
    }
}