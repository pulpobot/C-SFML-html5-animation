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

    sf::RenderWindow window(sf::VideoMode(400, 400), "Two Segments 1", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    sf::Font font;
    if(!font.loadFromFile("res/cour.ttf")){
        std::cerr << "Error loading cour.ttf file" << std::endl;
        return -1;
    }

    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(15);
    infoText.setFillColor(sf::Color::Black);
    infoText.setPosition(sf::Vector2f(10,window.getSize().y - 30));
    infoText.setString("Press and drag slider handles with mouse.");

    Segment segment0 = Segment(100, 20);
    Segment segment1 = Segment(100, 20);
    Slider slider0 = Slider(-90,90,0);
    Slider slider1 = Slider(-90,90,0);

    segment0.SetX(100);
    segment0.SetY(100);

    slider0.SetX(320);
    slider0.SetY(20);
    slider0.onChange = &OnHandleMoveCallback;

    slider1.SetX(340);
    slider1.SetY(20);
    slider1.onChange = &OnHandleMoveCallback;

    bool mouseOnSlider0 = false;
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
                    slider0.CaptureMouse(mousePos);
                    slider1.CaptureMouse(mousePos);
                    break;
                case sf::Event::MouseButtonReleased:
                    slider0.OnMouseRelease();
                    slider1.OnMouseRelease();
                    break;
                case sf::Event::MouseMoved:
                    mousePos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                    slider0.OnMouseMove(mousePos);
                    slider1.OnMouseMove(mousePos);
                    break;
            }
        }

        segment0.SetRotation(slider0.value);
        segment1.SetRotation(slider1.value);
        segment1.SetPosition(segment0.GetPin());
        window.clear(sf::Color::White);
        segment0.Draw(window);
        slider0.Draw(window);
        segment1.Draw(window);
        slider1.Draw(window);
        window.draw(infoText);
        window.display();
    }
}