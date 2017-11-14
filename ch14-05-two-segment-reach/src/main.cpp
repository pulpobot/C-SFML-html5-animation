#include <iostream>
#include <cmath>
#include "SFML\Graphics.hpp"
#include "Segment.h"

sf::Vector2f Reach(Segment &segment, const float xPos, const float yPos) {
    float dx = xPos - segment.GetX(),
            dy = yPos - segment.GetY();

    segment.SetRotation(std::atan2(dy, dx) * 180 / M_PI);

    float w = segment.GetPin().x - segment.GetX(),
            h = segment.GetPin().y - segment.GetY();

    return sf::Vector2f(xPos - w, yPos - h);
}

void Position(Segment &segmentA, Segment &segmentB)
{
    segmentA.SetPosition(segmentB.GetPin().x, segmentB.GetPin().y);
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Two Segment Reach", sf::Style::Titlebar | sf::Style::Close,
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

    Segment segment1 = Segment(100, 20);
    segment1.SetPosition(window.getSize().x / 2, window.getSize().y / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    sf::Vector2f target = Reach(segment0, event.mouseMove.x , event.mouseMove.y);
                    Reach(segment1, target.x, target.y);
                    Position(segment0, segment1);
                    break;
            }
        }

        window.clear(sf::Color::White);
        window.draw(infoText);
        segment0.Draw(window);
        segment1.Draw(window);
        window.display();
    }

}