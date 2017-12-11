#include <iostream>
#include <cmath>
#include <random>
#include "SFML\Graphics.hpp"
#include "Ball.h"

bool DetectCollision(float x, float y, Ball &ball){
    float dx = x - ball.GetX(),
    dy = y - ball.GetY(),
    dist = std::sqrt(dx * dx + dy * dy);
    return (dist < ball.shape.getRadius());
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Random 8", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 m(std::time(NULL));
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    Ball ball0(100, window.getSize().y / 2, 40, sf::Color::Red);
    Ball ball1(300, window.getSize().y / 2, 80, sf::Color::Red);

    std::vector<sf::CircleShape> dots;
    int numBalls = 300,
            iterations = 6;

    while (numBalls--) {
        //initialize variables
        float x = 0;
        float y = 0;

        //if x, y not in ballA AND not in ballB, set new random position
        while (!DetectCollision(x, y, ball0) && !DetectCollision(x,y, ball1)){
            //get random position on canvas
            x = window.getSize().x * dist(m);
            y = window.getSize().y * dist(m);
        }

        dots.emplace_back(sf::CircleShape(2));
        dots[dots.size() - 1].setOrigin(2, 2);
        dots[dots.size() - 1].setPosition(x, y);
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