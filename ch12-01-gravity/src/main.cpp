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

void Move(std::vector<Ball> &particles, int i){
    particles[i].Translate(particles[i].vx, particles[i].vy);

    for (int j = i + 1; j < particles.size(); ++j) {
         Gravitate(particles[i], particles[j]);
    }
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Gravity", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 m(std::time(NULL));
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    std::vector<Ball> particles;
    int numParticles = 30;

    for (int i = 0; i < numParticles; ++i) {
        particles.emplace_back(Ball(dist(m) * window.getSize().x, dist(m) * window.getSize().y, 5, sf::Color::Red));
        particles[i].mass = 1;
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