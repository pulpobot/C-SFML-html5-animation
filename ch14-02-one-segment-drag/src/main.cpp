#include <iostream>
#include <cmath>
#include "SFML\Graphics.hpp"
#include "Segment.h"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "One Segment Drag", sf::Style::Titlebar | sf::Style::Close,
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

    Segment segment0 = Segment(100, 20);
    segment0.SetPosition(window.getSize().x / 2, window.getSize().y / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    float dx = event.mouseMove.x - segment0.GetX();
                    float dy = event.mouseMove.y - segment0.GetY();
                    segment0.SetRotation(std::atan2(dy, dx) * 180 / M_PI);

                    float w = segment0.GetPin().x - segment0.GetX();
                    float h = segment0.GetPin().y - segment0.GetY();

                    segment0.SetPosition(event.mouseMove.x - w, event.mouseMove.y - h);
                    break;
            }
        }

        window.clear(sf::Color::White);
        window.draw(infoText);
        segment0.Draw(window);
        window.display();
    }

}