#include "SFML\Graphics.hpp"
#include <iostream>
#include "Ball.h"

const float EASING = 0.05f;

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Easing Off", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Ball ball(0, window.getSize().y / 2, 30, sf::Color::Red);

    sf::Font font;

    if (!font.loadFromFile("res/cour.ttf")) {
        std::cout << "Cannot find cour.ttf file";
        return -1;
    }

    sf::Text descText;
    descText.setPosition(10, window.getSize().y - 20);
    descText.setFont(font);
    descText.setCharacterSize(15);
    descText.setFillColor(sf::Color::Black);

    float targetX = window.getSize().x / 2;
    float targetY = window.getSize().y / 2;

    bool easing = true;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        if(easing){
            float dx = targetX - ball.GetX();
            if (std::abs(dx) < 1) {
                ball.SetX(targetX);
                easing = false;
                descText.setString("Animation done!");
            }
            else{
                float vx = dx * EASING;
                ball.Translate(vx, 0);
            }
        }

        window.clear(sf::Color::White);
        window.draw(descText);
        window.draw(ball.shape);
        window.display();
    }
}