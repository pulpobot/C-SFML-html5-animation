#include <iostream>
#include <cmath>
#include "SFML\Graphics.hpp"
#include "Segment.h"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Walking 2", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Segment segment0 = Segment(100, 20);
    Segment segment1 = Segment(100, 20);

    segment0.SetX(200);
    segment0.SetY(200);

    segment1.SetPosition(segment0.GetPin());

    float cycle = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        float angle0 = (std::sin(cycle) * 45 + 90);
        float angle1 = (std::sin(cycle) * 45 + 45);

        segment0.SetRotation(angle0);
        segment1.SetRotation(segment0.shape.getRotation() + angle1);
        segment1.SetPosition(segment0.GetPin());
        window.clear(sf::Color::White);
        segment0.Draw(window);
        segment1.Draw(window);
        window.display();

        cycle += 0.02f;
    }
}