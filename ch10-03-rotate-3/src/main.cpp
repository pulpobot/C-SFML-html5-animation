#include <iostream>
#include <cmath>
#include <random>
#include "SFML\Graphics.hpp"
#include "Ball.h"

void Move(Ball &ball, float cos, float sin, float centerX, float centerY) {
    float x1 = ball.GetX() - centerX;
    float y1 = ball.GetY() - centerY;
    float x2 = cos * x1 - sin * y1;
    float y2 = cos * y1 + sin * x1;

    ball.SetX(centerX + x2);
    ball.SetY(centerY + y2);
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Rotate 3", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    sf::Font font;
    if(!font.loadFromFile("res/cour.ttf")){
        std::cerr << "Error loading cour.ttf file" << std::endl;
        return  -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setPosition(10,10);
    text.setCharacterSize(15);
    text.setString("Move mouse left or right on window.");

    std::mt19937 mt(time(NULL));
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    float cos = 1;
    float sin = 0;
    float centerX = window.getSize().x / 2;
    float centerY = window.getSize().y / 2;

    std::vector<Ball> balls;
    int numBalls = 10;

    for (int j = 0; j < numBalls; ++j) {
        balls.emplace_back(Ball(dist(mt) * window.getSize().x, dist(mt) * window.getSize().y, 40, sf::Color::Red));
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseMoved:
                    float angle = (event.mouseMove.x - centerX) * 0.0005;
                    cos = std::cos(angle);
                    sin = std::sin(angle);
            }
        }

        window.clear(sf::Color::White);
        window.draw(text);
        for (int j = 0; j < numBalls; ++j) {
            Move(balls[j], cos, sin, centerX, centerY);
            window.draw(balls[j].shape);
        }
        window.display();
    }
}