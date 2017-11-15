#include <iostream>
#include <random>
#include "SFML\Graphics.hpp"
#include "Ball.h"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Bounce 3D", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 m(time(NULL));
    std::uniform_real_distribution<float> t(0.0f, 1.0f);

    Ball ball(0, 0, 40, sf::Color::Red);
    float xPos = 0,
            yPos = 0,
            zPos = 0,
            vx = t(m) * 10 - 5,
            vy = t(m) * 10 - 5,
            vz = t(m) * 10 - 5,
            fl = 250,
            vpX = window.getSize().x / 2.0f,
            vpY = window.getSize().y / 2.0f,
            top = -100,
            bottom = 100,
            left = -100,
            right = 100,
            front = -100,
            back = 100;

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

        xPos += vx;
        yPos += vy;
        zPos += vz;

        //check boundaries
        if(xPos + ball.shape.getRadius() > right){
            xPos = right - ball.shape.getRadius();
            vx *= -1;
        } else if(xPos - ball.shape.getRadius() < left){
            xPos = left + ball.shape.getRadius();
            vx *= -1;
        }

        if(yPos + ball.shape.getRadius() > bottom){
            yPos = bottom - ball.shape.getRadius();
            vy *= -1;
        } else if(yPos - ball.shape.getRadius() < top){
            yPos = top + ball.shape.getRadius();
            vy *= -1;
        }

        if(zPos + ball.shape.getRadius() > back){
            zPos = back - ball.shape.getRadius();
            vz *= -1;
        } else if(zPos - ball.shape.getRadius() < front){
            zPos = front + ball.shape.getRadius();
            vz *= -1;
        }

        if (zPos > -fl) {
            float scale = fl / (fl + zPos);
            ball.shape.setScale(scale, scale);
            ball.SetPosition(vpX + xPos * scale, vpY + yPos * scale);
            window.draw(ball.shape);
        }

        window.display();
    }

}
