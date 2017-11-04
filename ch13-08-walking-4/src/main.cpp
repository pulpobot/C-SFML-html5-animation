#include <iostream>
#include <cmath>
#include "SFML\Graphics.hpp"
#include "Segment.h"

const float offset = -M_PI / 2;

void Walk(Segment &segA, Segment &segB, float cyc) {
    float angle0 = (std::sin(cyc) * 45 + 90),
            angle1 = (sin(cyc + offset) * 45 + 45);
    segA.SetRotation(angle0);
    segB.SetRotation(segA.shape.getRotation() + angle1);
    segB.SetPosition(segA.GetPin());
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Walking 4", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Segment segment0 = Segment(100, 30);
    Segment segment1 = Segment(100, 20);
    Segment segment2 = Segment(100, 30);
    Segment segment3 = Segment(100, 20);

    segment0.SetX(200);
    segment0.SetY(200);
    segment1.SetPosition(segment0.GetPin());

    segment2.SetX(200);
    segment2.SetY(200);
    segment3.SetPosition(segment0.GetPin());

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

        Walk(segment0, segment1, cycle);
        Walk(segment2, segment3, cycle + M_PI);

        window.clear(sf::Color::White);
        segment0.Draw(window);
        segment1.Draw(window);
        segment2.Draw(window);
        segment3.Draw(window);
        window.display();

        cycle += 0.02f;
    }
}