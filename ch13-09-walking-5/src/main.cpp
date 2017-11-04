#include <iostream>
#include <cmath>
#include "SFML\Graphics.hpp"
#include "Segment.h"
#include "Slider.h"

Slider speedSlider, thighRangeSlider, thighBaseSlider, calfRangeSlider, calfOffsetSlider;

void OnHandleMoveCallback(Slider *slider){
    slider->handle.setPosition(slider->background.getPosition().x, slider->handleY + slider->background.getPosition().y);
}

void Walk(Segment &segA, Segment &segB, float cyc) {
    float angle0 = (std::sin(cyc) * thighRangeSlider.value + thighBaseSlider.value),
            angle1 = (sin(cyc + calfOffsetSlider.value) * calfRangeSlider.value + calfRangeSlider.value);
    segA.SetRotation(angle0);
    segB.SetRotation(segA.shape.getRotation() + angle1);
    segB.SetPosition(segA.GetPin());
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Walking 5", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    sf::Font font;
    if(!font.loadFromFile("res/cour.ttf")){
        std::cerr << "Error loading cout.ttf file" << std::endl;
        return -1;
    }

    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(15);
    infoText.setFillColor(sf::Color::Black);
    infoText.setPosition(sf::Vector2f(10,0));
    infoText.setString("Press and drag slider handles with mouse.");

    speedSlider = Slider(0, 0.2, 0.08),
            thighRangeSlider = Slider(0, 90, 45),
            thighBaseSlider = Slider(0, 180, 90),
            calfRangeSlider = Slider(0, 90, 45),
            calfOffsetSlider = Slider(-M_PI, M_PI, -M_PI/2);

    speedSlider.onChange = &OnHandleMoveCallback;
    thighRangeSlider.onChange = &OnHandleMoveCallback;
    thighBaseSlider.onChange = &OnHandleMoveCallback;
    calfRangeSlider.onChange = &OnHandleMoveCallback;
    calfOffsetSlider.onChange = &OnHandleMoveCallback;

    speedSlider.SetX(10);
    speedSlider.SetY(20);
    thighRangeSlider.SetX(30);
    thighRangeSlider.SetY(20);
    thighBaseSlider.SetX(50);
    thighBaseSlider.SetY(20);
    calfRangeSlider.SetX(70);
    calfRangeSlider.SetY(20);
    calfOffsetSlider.SetX(90);
    calfOffsetSlider.SetY(20);

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
            sf::Vector2f mousePos;
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    speedSlider.CaptureMouse(mousePos);
                    thighRangeSlider.CaptureMouse(mousePos);
                    thighBaseSlider.CaptureMouse(mousePos);
                    calfRangeSlider.CaptureMouse(mousePos);
                    calfOffsetSlider.CaptureMouse(mousePos);
                    break;
                case sf::Event::MouseButtonReleased:
                    speedSlider.OnMouseRelease();
                    thighRangeSlider.OnMouseRelease();
                    thighBaseSlider.OnMouseRelease();
                    calfRangeSlider.OnMouseRelease();
                    calfOffsetSlider.OnMouseRelease();
                    break;
                case sf::Event::MouseMoved:
                    mousePos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                    speedSlider.OnMouseMove(mousePos);
                    thighRangeSlider.OnMouseMove(mousePos);
                    thighBaseSlider.OnMouseMove(mousePos);
                    calfRangeSlider.OnMouseMove(mousePos);
                    calfOffsetSlider.OnMouseMove(mousePos);
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

        speedSlider.Draw(window);
        thighRangeSlider.Draw(window);
        thighBaseSlider.Draw(window);
        calfRangeSlider.Draw(window);
        calfOffsetSlider.Draw(window);
        window.draw(infoText);
        window.display();

        cycle += speedSlider.value;
    }
}