#include <iostream>
#include <cmath>
#include "random"
#include "SFML\Graphics.hpp"
#include "Segment.h"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Cosines 1", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("res/cour.ttf")) {
        std::cerr << "Error loading cour.ttf file" << std::endl;
        return -1;
    }

    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(15);
    infoText.setFillColor(sf::Color::Black);
    infoText.setPosition(sf::Vector2f(10, window.getSize().y - 20));
    infoText.setString("Move mouse on window.");

    Segment segment0(100, 20);
    Segment segment1(100, 20);

    segment1.SetPosition(window.getSize().x / 2, window.getSize().y / 2);

    sf::Vector2f mousePos(0, 0);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    mousePos.x = event.mouseMove.x;
                    mousePos.y = event.mouseMove.y;
                    break;
            }
        }

        float dx = mousePos.x - segment1.GetX(),
                dy = mousePos.y - segment1.GetY(),
                dist = std::sqrt(dx * dx + dy * dy),
                a = 100,
                b = 100,
                c = std::fminf(dist, a + b),
                B = std::acos((b * b - a * a - c * c) / (-2 * a * c)),
                C = std::acos((c * c - a * a - b * b) / (-2 * a * b)),
                D = std::atan2(dy, dx),
                E = D + B + M_PI + C;

        segment1.SetRotation((D + B) * 180 / M_PI);

        segment0.SetPosition(segment1.GetPin());
        segment0.SetRotation(E * 180 / M_PI);

        window.clear(sf::Color::White);
        window.draw(infoText);
        segment0.Draw(window);
        segment1.Draw(window);
        window.display();
    }

}