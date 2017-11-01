#include <iostream>
#include "SFML\Graphics.hpp"
#include "Segment.h"
#include "Utils.h"
#include "Slider.h"

void OnHandleMoveCallback(Slider *slider){
    slider->handle.setPosition(slider->background.getPosition().x, slider->handleY + slider->background.getPosition().y);
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Single Segment", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Segment segment = Segment(100, 20);
    segment.SetX(100);
    segment.SetY(100);

    Slider slider = Slider(-90,90,0);
    slider.SetX(300);
    slider.SetY(20);
    slider.onChange = &OnHandleMoveCallback;

    bool mouseOnSlider = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            sf::Vector2f mousePos;
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    slider.CaptureMouse(mousePos);
                    break;
                case sf::Event::MouseButtonReleased:
                    slider.OnMouseRelease();
                    break;
                case sf::Event::MouseMoved:
                    mousePos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                    slider.OnMouseMove(mousePos);
                    break;
            }
        }

        segment.SetRotation(slider.value);
        window.clear(sf::Color::White);
        segment.Draw(window);
        slider.Draw(window);
        window.display();
    }
}