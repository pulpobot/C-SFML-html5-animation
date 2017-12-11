#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include "Ball.h"

const float BOUNCE = -0.7f;

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Sound Events", sf::Style::Titlebar | sf::Style::Close, context);
    window.setFramerateLimit(60);

    sf::SoundBuffer buffer;
    if(!buffer.loadFromFile("res/boing.wav")){
        std::cerr << "Error loading boing.wav file" << std::endl;
        return -1;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);

    std::mt19937 mt(time(NULL));
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    Ball ball = Ball(window.getSize().x / 2, window.getSize().y / 2, 30, sf::Color::Red);
    ball.vx = dist(mt) * 10 - 5;
    ball.vy = dist(mt) * 10 - 5;

    float left = 0;
    float right = window.getSize().x;
    float top = 0;
    float bottom = window.getSize().y;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        window.clear(sf::Color::White);

        ball.Draw(window);

        sf::Vector2f ballPos = ball.shape.getPosition();
        if (ballPos.x + ball.shape.getRadius() > right) {
            ball.SetX(right - ball.shape.getRadius());
            ball.vx *= BOUNCE;
            sound.play();
        } else if(ballPos.x - ball.shape.getRadius() < left){
            ball.SetX(left + ball.shape.getRadius());
            ball.vx *= BOUNCE;
            sound.play();
        }

        if (ballPos.y + ball.shape.getRadius() > bottom) {
            ball.SetY(bottom - ball.shape.getRadius());
            ball.vy *= BOUNCE;
            sound.play();
        } else if(ballPos.y - ball.shape.getRadius() < top){
            ball.SetY(top + ball.shape.getRadius());
            ball.vy *= BOUNCE;
            sound.play();
        }

        window.display();
    }

    return 0;
}