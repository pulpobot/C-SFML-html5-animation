#include <iostream>
#include <cmath>
#include "random"
#include "SFML\Graphics.hpp"
#include "Segment.h"
#include "Ball.h"

const float GRAVITY = 0.5f;
const float BOUNCE = -0.9f;
std::mt19937 m(std::time(NULL));
std::uniform_real_distribution<double> dt(0.0, 1.0);

sf::Vector2f Reach(Segment &segment, const float xPos, const float yPos) {
    float dx = xPos - segment.GetX(),
            dy = yPos - segment.GetY();

    segment.SetRotation(std::atan2(dy, dx) * 180 / M_PI);

    float w = segment.GetPin().x - segment.GetX(),
            h = segment.GetPin().y - segment.GetY();

    return sf::Vector2f(xPos - w, yPos - h);
}

void Position(Segment &segmentA, Segment &segmentB) {
    segmentA.SetPosition(segmentB.GetPin().x, segmentB.GetPin().y);
}

void MoveBall(Ball &ball, const sf::Vector2u windowSize) {
    ball.vy += GRAVITY;
    ball.Translate(ball.vx, ball.vy);

    if (ball.GetX() + ball.shape.getRadius() > windowSize.x) {
        ball.SetX(windowSize.x - ball.shape.getRadius());
        ball.vx *= BOUNCE;
    } else if (ball.GetX() - ball.shape.getRadius() < 0) {
        ball.SetX(ball.shape.getRadius());
        ball.vx *= BOUNCE;
    }

    if (ball.GetY() + ball.shape.getRadius() > windowSize.y) {
        ball.SetY(windowSize.y - ball.shape.getRadius());
        ball.vy *= BOUNCE;
    } else if (ball.GetY() - ball.shape.getRadius() < 0) {
        ball.SetY(ball.shape.getRadius());
        ball.vy *= BOUNCE;
    }
}

void CheckHit(Segment &segment, Ball &ball) {
    float dx = segment.GetPin().x - ball.GetX(),
            dy = segment.GetPin().y - ball.GetY(),
            dist = std::sqrt(dx * dx + dy * dy);

    if (dist < ball.shape.getRadius()) {
        ball.vx += dt(m) * 2 - 1;
        ball.vy -= 1;
    }

}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Play Ball", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Ball ball(0, 0, 20, sf::Color::Red);
    ball.vx = 10;

    std::vector<Segment> segments = std::vector<Segment>();
    int numSegment = 5;

    while (numSegment--) {
        segments.emplace_back(Segment(20, 10));
    }

    //center the last one
    segments[segments.size() - 1].SetPosition(window.getSize().x / 2, window.getSize().y / 2);

    sf::Vector2f mousePos(0, 0);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    mousePos.x = event.mouseMove.x;
                    mousePos.y = event.mouseMove.y;
                    break;
            }
        }

        MoveBall(ball, window.getSize());

        sf::Vector2f target = Reach(segments[0], ball.GetX(), ball.GetY());
        for (int i = 1; i < segments.size(); ++i) {
            target = Reach(segments[i], target.x, target.y);
            Position(segments[i - 1], segments[i]);
        }
        CheckHit(segments[0], ball);
        window.clear(sf::Color::White);
        for (int i = 0; i < segments.size(); ++i) {
            segments[i].Draw(window);
        }
        window.draw(ball.shape);
        window.display();
    }

}