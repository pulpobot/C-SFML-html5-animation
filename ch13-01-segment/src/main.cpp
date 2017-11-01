#include <iostream>
#include "SFML\Graphics.hpp"
#include "Segment.h"
#include "Utils.h"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Segment", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Segment segment0 = Segment(100, 20);
    segment0.SetX(100);
    segment0.SetY(50);

    Segment segment1 = Segment(200, 10);
    segment1.SetX(100);
    segment1.SetY(80);

    Segment segment2 = Segment(80, 40);
    segment2.SetX(100);
    segment2.SetY(120);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        window.clear(sf::Color::White);
        segment0.Draw(window);
        segment1.Draw(window);
        segment2.Draw(window);
        window.display();
    }
}