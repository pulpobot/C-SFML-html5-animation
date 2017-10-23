#include <iostream>
#include <cmath>
#include "SFML\Graphics.hpp"
#include "Line.h"
#include "Ball.h"

const float GRAVITY = 0.2f;
const float BOUNCE = -0.6f;

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Angle Bounce Optimized", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Ball ball(100, 100, 40, sf::Color::Red);

    Line line(50, 200, 300, sf::Color::Black);
    line.Rotate(10);

    float cos = std::cos(line.Rotation() * M_PI / 180);
    float sin = std::sin(line.Rotation()* M_PI / 180);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        //normal motion code
        ball.vy += GRAVITY;
        ball.Translate(ball.vx, ball.vy);

        //get position of ball, relative to line
        float x1 = ball.GetX() - line.GetX();
        float y1 = ball.GetY() - line.GetY();

        //rotate coordinates
        float y2 = cos * y1 - sin * x1;

       //perform bounce with rotated values
        if(y2 > -ball.shape.getRadius()){
            //rotate coordinates
            float x2 = cos * x1 + sin * y1;

            //rotate velocity
            float vx1 = cos * ball.vx + sin * ball.vy;
            float vy1 = cos * ball.vy - sin * ball.vx;

            y2 = -ball.shape.getRadius();
            vy1 *= BOUNCE;

            //rotate everything back
            x1 = cos * x2 - sin * y2;
            y1 = cos * y2 + sin * x2;
            ball.vx = cos * vx1 - sin * vy1;
            ball.vy = cos * vy1 + sin * vx1;
            ball.SetX(line.GetX() + x1);
            ball.SetY(line.GetY() + y1);
        }

        window.clear(sf::Color::White);
        window.draw(ball.shape);
        window.draw(line.shape);
        window.display();
    }
}