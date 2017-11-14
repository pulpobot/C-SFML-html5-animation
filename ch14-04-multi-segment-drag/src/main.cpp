#include <iostream>
#include <cmath>
#include "SFML\Graphics.hpp"
#include "Segment.h"

void drag(Segment &segment, const float xPos, const float yPos) {
    float dx = xPos - segment.GetX();
    float dy = yPos - segment.GetY();

    segment.SetRotation(std::atan2(dy, dx) * 180 / M_PI);

    float w = segment.GetPin().x - segment.GetX();
    float h = segment.GetPin().y - segment.GetY();

    segment.SetPosition(xPos - w, yPos - h);

}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Multi Segment Drag", sf::Style::Titlebar | sf::Style::Close,
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

    std::vector<Segment> segments = std::vector<Segment>();
    int numSegments = 5;

    while(numSegments--)
    {
        segments.emplace_back(Segment(50, 10));
    }

    sf::Vector2f mousePos = sf::Vector2f(0,0);
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

        drag(segments[0], mousePos.x, mousePos.y);

        for (int i = 1; i < segments.size(); ++i) {
            drag(segments[i], segments[i-1].GetX(), segments[i-1].GetY());
        }

        window.clear(sf::Color::White);
        window.draw(infoText);
        for (int i = 0; i < segments.size(); ++i) {
            segments[i].Draw(window);
        }
        window.display();
    }

}