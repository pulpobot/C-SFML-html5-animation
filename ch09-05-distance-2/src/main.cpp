#include <iostream>
#include <cmath>
#include <random>
#include "SFML\Graphics.hpp"
#include "Ball.h"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Distance 2", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 mt(std::time(NULL));
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    Ball ballA(window.getSize().x / 2, window.getSize().y / 2, dist(mt) * 100, sf::Color::Red);
    Ball ballB(0, 0, dist(mt) * 100, sf::Color::Red);

    sf::Font font;
    if (!font.loadFromFile("res/cour.ttf")) {
        std::cerr << "Error loading cout.ttf file" << std::endl;
        return -1;
    }

    sf::Text hitText;
    hitText.setFont(font);
    hitText.setCharacterSize(15);
    hitText.setFillColor(sf::Color::Black);
    hitText.setPosition(sf::Vector2f(10, 10));

    window.clear(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    ballB.SetX(event.mouseMove.x);
                    ballB.SetY(event.mouseMove.y);

                    float dx = ballB.GetX() - ballA.GetX();
                    float dy = ballB.GetY() - ballA.GetY();
                    float dist = std::sqrt(dx * dx + dy * dy);

                    if (dist < ballA.shape.getRadius() + ballB.shape.getRadius())
                        hitText.setString("Hit");
                    else
                        hitText.setString("");
            }
        }
        window.clear(sf::Color::White);
        window.draw(hitText);
        window.draw(ballA.shape);
        window.draw(ballB.shape);
        window.display();
    }
}