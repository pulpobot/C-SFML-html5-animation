#include <iostream>
#include "SFML\Graphics.hpp"
#include <random>
#include "Ball.h"
#include "Utils.h"

const float SPRING = 0.03f;
const float FRICTION = 0.9f;

void ApplyHandle(Ball &ball, Ball &handle) {
    float dx = handle.GetX() - ball.GetX();
    float dy = handle.GetY()- ball.GetY();
    float ax = dx * SPRING;
    float ay = dy * SPRING;
    ball.vx += ax;
    ball.vy += ay;
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Multi Spring", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 mt(time(NULL));
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    Ball mainBall(window.getSize().x / 2, window.getSize().y / 2, 20, sf::Color::Red);
    std::vector<Ball> handles;
    int numHandles = 3;

    for (int i = 0; i < numHandles; ++i) {
        handles.emplace_back(dist(mt) * window.getSize().x, dist(mt) * window.getSize().y, 10, sf::Color::Blue);
    }

    float mouseX = window.getSize().x / 2;
    float mouseY = window.getSize().y / 2;

    bool isMousePressed = false;
    Ball * handleBeingDragged;
    std::vector<sf::Vertex> line;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    for (int i = 0; i < handles.size(); ++i) {
                        if(Utils::ContainsPoint(handles[i].GetBounds(), mouseX, mouseY))
                        {
                            isMousePressed = true;
                            handleBeingDragged = &handles[i];
                            break;
                        }
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    isMousePressed = false;
                    break;
                case sf::Event::MouseMoved:
                    mouseX = event.mouseMove.x;
                    mouseY = event.mouseMove.y;
                    if (isMousePressed) {
                        (*handleBeingDragged).SetX(mouseX);
                        (*handleBeingDragged).SetY(mouseY);
                    }
                    break;
            }
        }

        window.clear(sf::Color::White);

        for (int i = 0; i < handles.size(); ++i) {
            ApplyHandle(mainBall, handles[i]);
        }

        mainBall.vx *= FRICTION;
        mainBall.vy *= FRICTION;
        mainBall.Translate(mainBall.vx, mainBall.vy);

        for (int i = 0; i < handles.size(); ++i) {
            line.clear();
            line.emplace_back(sf::Vertex(sf::Vector2f(mainBall.GetX(), mainBall.GetY()), sf::Color::Black));
            line.emplace_back(sf::Vertex(sf::Vector2f(handles[i].GetX(), handles[i].GetY()), sf::Color::Black));
            window.draw(&line[0], line.size(), sf::PrimitiveType::LinesStrip);
            window.draw(handles[i].shape);
        }

        window.draw(mainBall.shape);

        window.display();
    }
}