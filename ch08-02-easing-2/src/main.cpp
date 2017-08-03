#include "SFML\Graphics.hpp"
#include <iostream>
#include "Ball.h"
#include "Utils.h"

const float EASING = 0.05f;

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Easing 2", sf::Style::Titlebar | sf::Style::Close,
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
    descText.setString("Press and drag circle with mouse.");
    descText.setCharacterSize(15);
    descText.setFillColor(sf::Color::Black);

    float targetX = window.getSize().x / 2;
    float targetY = window.getSize().y / 2;

    bool isMouseDown = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (Utils::ContainsPoint(ball.GetBounds(), event.mouseButton.x, event.mouseButton.y))
                        isMouseDown = true;
                    break;
                case sf::Event::MouseButtonReleased:
                    isMouseDown = false;
                    break;
                case sf::Event::MouseMoved:
                    if (isMouseDown) {
                        ball.SetX(event.mouseMove.x);
                        ball.SetY(event.mouseMove.y);
                    }
            }
        }

        if (!isMouseDown) {
            float vx = (targetX - ball.GetX()) * EASING;
            float vy = (targetY - ball.GetY()) * EASING;
            ball.Translate(vx, vy);
        }

        window.clear(sf::Color::White);
        window.draw(descText);
        window.draw(ball.shape);
        window.display();
    }
}