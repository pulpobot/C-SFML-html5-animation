#include "SFML\Graphics.hpp"
#include <iostream>
#include "Ball.h"
#include "Utils.h"

const float EASING = 0.05f;

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Easing to Mouse", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Ball ball(0, 0, 30, sf::Color::Red);

    sf::Font font;

    if (!font.loadFromFile("res/cour.ttf")) {
        std::cout << "Cannot find cour.ttf file";
        return -1;
    }

    sf::Text descText;
    descText.setPosition(10, window.getSize().y - 20);
    descText.setFont(font);
    descText.setString("Move mouse on canvas.");
    descText.setCharacterSize(15);
    descText.setFillColor(sf::Color::Black);

    float targetX = 0;
    float targetY = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    targetX = event.mouseMove.x;
                    targetY = event.mouseMove.y;
            }
        }

        float vx = (targetX - ball.GetX()) * EASING;
        float vy = (targetY - ball.GetY()) * EASING;
        ball.Translate(vx, vy);

        window.clear(sf::Color::White);
        window.draw(descText);
        window.draw(ball.shape);
        window.display();
    }
}