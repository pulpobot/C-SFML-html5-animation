#include <iostream>
#include <random>
#include <algorithm>
#include "SFML\Graphics.hpp"
#include "ball3d.h"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Spring 3D", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("res/cour.ttf")) {
        std::cerr << "Error loading cour.ttf file" << std::endl;
        return -1;
    }

    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(10);
    infoText.setFillColor(sf::Color::Black);
    infoText.setPosition(sf::Vector2f(5, window.getSize().y - 20));
    infoText.setString("Click window to set random target.");

    std::mt19937 m(time(NULL));
    std::uniform_real_distribution<float> t(0.0f, 1.0f);

    Ball3d ball(0, 0, 0, 40, sf::Color::Red);
    float fl = 250,
            vpX = 0,
            vpY = 0,
            tx = t(m) * 500 - 250,
            ty = t(m) * 500 - 250,
            tz = t(m) * 500,
            spring = 0.1,
            friction = 0.94f;

    vpX = window.getSize().x / 2.0f;
    vpY = window.getSize().y / 2.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left){
                        tx = t(m) * 500 - 250;
                        ty = t(m) * 500 - 250;
                        tz = t(m) * 500;
                    }
                    break;
            }
        }

        float dx = tx - ball.xPos,
                dy = ty - ball.yPos,
                dz = tz - ball.zPos;

        ball.vx += dx * spring;
        ball.vy += dy * spring;
        ball.vz += dz * spring;

        ball.xPos += ball.vx;
        ball.yPos += ball.vy;
        ball.zPos += ball.vz;

        ball.vx *= friction;
        ball.vy *= friction;
        ball.vz *= friction;

        if (ball.zPos > -fl) {
            float scale = fl / (fl + ball.zPos);
            ball.shape.setScale(sf::Vector2f(scale, scale));
            ball.SetX(vpX + ball.xPos * scale);
            ball.SetY(vpY + ball.yPos * scale);
            ball.visible = true;
        } else
            ball.visible = false;

        window.clear(sf::Color::White);
        ball.Draw(window);
        window.draw(infoText);
        window.display();
    }

}
