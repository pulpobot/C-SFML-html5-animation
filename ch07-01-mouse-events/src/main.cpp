#include "SFML\Graphics.hpp"
#include <iostream>
#include "Utils.h"
#include "Ball.h"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400,400), "Mouse Events", sf::Style::Titlebar | sf::Style::Close, context);
    window.setFramerateLimit(60);
    sf::Clock clickClock;
    sf::Font font;

    if (!font.loadFromFile("res/cour.ttf")) {
        std::cout << "Cannot find cour.ttf file";
        return -1;
    }

    sf::Text debugText;
    debugText.setPosition(10, 10);
    debugText.setFont(font);
    debugText.setFillColor(sf::Color::Black);
    debugText.setCharacterSize(15);

    Ball ball(window.getSize().x / 2, window.getSize().y / 2, 30, sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (Utils::ContainsPoint(ball.GetBounds(), event.mouseButton.x, event.mouseButton.y))
                        debugText.setString("in ball: mousedown");
                    else
                        debugText.setString("canvas: mousedown");
                    break;
                case sf::Event::MouseButtonReleased:
                    if (Utils::ContainsPoint(ball.GetBounds(), event.mouseButton.x, event.mouseButton.y))
                        debugText.setString("in ball: mouseup");
                    else
                        debugText.setString("canvas: mouseup");
                    break;
                case sf::Event::MouseMoved:
                    if (Utils::ContainsPoint(ball.GetBounds(), event.mouseMove.x, event.mouseMove.y))
                        debugText.setString("in ball: mousemove");
                    else
                        debugText.setString("canvas: mousemove");
                    break;
            }
        }

        window.clear(sf::Color::White);
        window.draw(debugText);
        ball.Draw(window);
        window.display();
    }
}