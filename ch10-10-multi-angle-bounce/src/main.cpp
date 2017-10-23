#include <iostream>
#include <cmath>
#include "SFML\Graphics.hpp"
#include "Line.h"
#include "Ball.h"
#include "Utils.h"

const float GRAVITY = 0.2f;
const float BOUNCE = -0.6f;

void CheckLine(Line &line, Ball &ball){
    sf::FloatRect bounds = line.GetBounds();

    float cos = std::cos(line.Rotation() * M_PI / 180);
    float sin = std::sin(line.Rotation() * M_PI / 180);

    if (ball.GetX() + ball.shape.getRadius() > bounds.left &&
        ball.GetX() - ball.shape.getRadius() < bounds.left + bounds.width) {
        //get position of ball, relative to line
        float x1 = ball.GetX() - line.GetX();
        float y1 = ball.GetY() - line.GetY();

        //rotate coordinates
        float y2 = cos * y1 - sin * x1;
        float vy1 = cos * ball.vy - sin * ball.vx;

        //perform bounce with rotated values
        if (y2 > -ball.shape.getRadius() && y2 < vy1) {
            //rotate coordinates
            float x2 = cos * x1 + sin * y1;

            //rotate velocity
            float vx1 = cos * ball.vx + sin * ball.vy;

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
    }
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Multi Angle Bounce", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Ball ball(100, 50, 20, sf::Color::Red);
    std::vector<Line> lines;

    lines.emplace_back(Line(50, 100, 100, sf::Color::Black));
    lines[0].SetRotation(30);

    lines.emplace_back(Line(50, 200, 100, sf::Color::Black));
    lines[1].SetRotation(45);

    lines.emplace_back(Line(170, 150, 100, sf::Color::Black));
    lines[2].SetRotation(-20);

    lines.emplace_back(Line(100, 330, 100, sf::Color::Black));
    lines[3].SetRotation(10);

    lines.emplace_back(Line(180, 250, 100, sf::Color::Black));
    lines[4].SetRotation(-30);

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

        //bounce of ceiling, floor and walls
        if (ball.GetX() + ball.shape.getRadius() > window.getSize().x) {
            ball.SetX(window.getSize().x - ball.shape.getRadius());
            ball.vx *= BOUNCE;
        } else if (ball.GetX() - ball.shape.getRadius() < 0) {
            ball.SetX(ball.shape.getRadius());
            ball.vx *= BOUNCE;
        }

        if (ball.GetY() + ball.shape.getRadius() > window.getSize().y) {
            ball.SetY(window.getSize().y - ball.shape.getRadius());
            ball.vy *= BOUNCE;
        } else if(ball.GetY() - ball.shape.getRadius() < 0){
            ball.SetY(ball.shape.getRadius());
            ball.vy *= BOUNCE;
        }

        window.clear(sf::Color::White);
        for (int i = 0; i < lines.size(); ++i) {
            CheckLine(lines[i], ball);
            window.draw(lines[i].shape);
        }
        window.draw(ball.shape);
        window.display();
    }
}