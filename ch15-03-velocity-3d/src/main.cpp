#include <iostream>
#include "SFML\Graphics.hpp"
#include "Ball.h"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Velocity 3D", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("res/cour.ttf")) {
        std::cerr << "Error loading cour.ttf file" << std::endl;
        return -1;
    }

    Ball ball(0, 0, 40, sf::Color::Red);
    float xPos = 0,
            yPos = 0,
            zPos = 0,
            vx = 0,
            vy = 0,
            vz = 0,
            friction = 0.98f,
            fl = 250,
            vpX = window.getSize().x / 2.0f,
            vpY = window.getSize().y / 2.0f;


    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(15);
    infoText.setFillColor(sf::Color::Black);
    infoText.setPosition(sf::Vector2f(10, window.getSize().y - 40));
    infoText.setString("Arrow keys move circle on x and y axis,\nshift/control key along the z-axis.");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == 71) { //left
                        vx -= 1;
                    } else if (event.key.code == 72) { //right
                        vx += 1;
                    } else if (event.key.code == 73) { //up
                        vy -= 1;
                    } else if (event.key.code == 74) { //down
                        vy += 1;
                    } else if (event.key.shift) { //shift
                        vz += 1;
                    } else if (event.key.control) { //control
                        vz -= 1;
                    }

                    break;
            }
        }

        window.clear(sf::Color::White);
        window.draw(infoText);

        xPos += vx;
        yPos += vy;
        zPos += vz;
        vx *= friction;
        vy *= friction;
        vz *= friction;

        if (zPos > -fl) {
            float scale = fl / (fl + zPos);
            ball.shape.setScale(scale, scale);
            ball.SetPosition(vpX + xPos * scale, vpY + yPos * scale);
            window.draw(ball.shape);
        }

        window.display();
    }

}
