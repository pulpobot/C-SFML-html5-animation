#include <iostream>
#include <cmath>
#include <random>
#include "SFML\Graphics.hpp"
#include "Ball.h"

void Gravitate(Ball &partA, Ball &partB){
    float dx = partB.GetX() - partA.GetX();
    float dy = partB.GetY() - partA.GetY();
    float distSQ = dx * dx + dy * dy;
    float dist = std::sqrt(distSQ);
    float force = partA.mass * partB.mass / distSQ;
    float ax = force * dx / dist;
    float ay = force * dy / dist;

    partA.vx += ax / partA.mass;
    partA.vy += ay / partA.mass;
    partB.vx -= ax / partB.mass;
    partB.vy -= ay / partB.mass;
}

sf::Vector2f Rotate(float x, float y, float sin, float cos, bool reverse) {
    sf::Vector2f result;
    result.x = (reverse) ? (x * cos + y * sin) : (x * cos - y * sin);
    result.y = (reverse) ? (y * cos - x * sin) : (y * cos + x * sin);
    return result;
}

void CheckCollision(Ball &ball0, Ball &ball1) {
    float dx = ball1.GetX() - ball0.GetX();
    float dy = ball1.GetY() - ball0.GetY();
    float dist = std::sqrt(dx * dx + dy * dy);

    if (dist < ball0.shape.getRadius() + ball1.shape.getRadius()) {
        //calculate angle, sine, and cosine
        float angle = std::atan2(dy, dx);
        float sin = std::sin(angle);
        float cos = std::cos(angle);

        //rotate ball0's position
        sf::Vector2f pos0(0, 0);

        //rotate balls1's position
        sf::Vector2f pos1(Rotate(dx, dy, sin, cos, true));

        //rotate ball0's velocity
        sf::Vector2f vel0(Rotate(ball0.vx, ball0.vy, sin, cos, true));

        //rotate ball1's velocity
        sf::Vector2f vel1(Rotate(ball1.vx, ball1.vy, sin, cos, true));

        //collision reaction
        float vxTotal = vel0.x - vel1.x;
        vel0.x = ((ball0.mass - ball1.mass) * vel0.x + 2 * ball1.mass * vel1.x) / (ball0.mass + ball1.mass);
        vel1.x = vxTotal + vel0.x;

        //update position - to avoid objects becoming stuck
        float absV = std::abs(vel0.x) + std::abs(vel1.x);
        float overlap = (ball0.shape.getRadius() + ball1.shape.getRadius()) - std::abs(pos0.x - pos1.x);
        pos0.x += vel0.x / absV * overlap;
        pos1.x += vel1.x / absV * overlap;

        //rotate positions back
        sf::Vector2f pos0F(Rotate(pos0.x, pos0.y, sin, cos, false));
        sf::Vector2f pos1F(Rotate(pos1.x, pos1.y, sin, cos, false));

        //adjust positions to actual screen position
        ball1.SetX(ball0.GetX() + pos1F.x);
        ball1.SetY(ball0.GetY() + pos1F.y);
        ball0.SetX(ball0.GetX() + pos0F.x);
        ball0.SetY(ball0.GetY() + pos0F.y);

        //rotate velocities back
        sf::Vector2f vel0F(Rotate(vel0.x, vel0.y, sin, cos, false));
        sf::Vector2f vel1F(Rotate(vel1.x, vel1.y, sin, cos, false));

        ball0.vx = vel0F.x;
        ball0.vy = vel0F.y;
        ball1.vx = vel1F.x;
        ball1.vy = vel1F.y;
    }
}

void Move(std::vector<Ball> &particles, int i){
    particles[i].Translate(particles[i].vx, particles[i].vy);

    for (int j = i + 1; j < particles.size(); ++j) {
        CheckCollision(particles[i], particles[j]);
         Gravitate(particles[i], particles[j]);
    }
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Gravity Random", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 m(std::time(NULL));
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    std::vector<Ball> particles;
    int numParticles = 30;

    for (int i = 0; i < numParticles; ++i) {
        float size = dist(m) * 20 + 5;
        particles.emplace_back(Ball(dist(m) * window.getSize().x, dist(m) * window.getSize().y, size, sf::Color::Red));
        particles[i].mass = size;
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

        for (int i = 0; i < numParticles; ++i) {
            Move(particles, i);
            window.draw(particles[i].shape);
        }

        window.display();
    }
}