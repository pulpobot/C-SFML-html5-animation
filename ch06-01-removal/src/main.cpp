#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Ball.h"

const int NUM_BALLS = 10;

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Removal", sf::Style::Titlebar | sf::Style::Close, context);
    window.setFramerateLimit(60);

    std::mt19937 mt(time(NULL));
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    sf::Font font;
    if(!font.loadFromFile("res/cour.ttf")){
        std::cout << "Error loading cour.ttf file" << std::endl;
        return -1;
    }

    sf::Text debugText;
    debugText.setFont(font);
    debugText.setCharacterSize(15);
    debugText.setFillColor(sf::Color::Black);
    debugText.setPosition(sf::Vector2f(10,10));

    std::vector<Ball> balls;

    for (int i = 0; i < NUM_BALLS; i++) {
        float x = dist(mt) * window.getSize().x;
        float y = dist(mt) * window.getSize().y;
        Ball ball = Ball(x, y, 20, sf::Color::Red);
        ball.id = "ball" + std::to_string(i);
        ball.vx = dist(mt) * 2 - 1;
        ball.vy = dist(mt) * 2 - 1;
        balls.push_back(ball);
    }

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

        std::vector<Ball>::iterator ball = balls.begin();
        while (ball != balls.end()) {
            ball->Draw(window);
            sf::Vector2f ballPos = ball->shape.getPosition();
            if (ballPos.x - ball->shape.getRadius() > window.getSize().x ||
                ballPos.x + ball->shape.getRadius() < 0 ||
                ballPos.y - ball->shape.getRadius() > window.getSize().y ||
                ballPos.y + ball->shape.getRadius() < 0) {
                //remove ball from array
                debugText.setString("Removed " + ball->id);
                ball = balls.erase(ball);
            } else
                ++ball;

        if (balls.size() == 0)
            debugText.setString("All gone!");
        }

        window.draw(debugText);
        window.display();
    }

    return 0;
}