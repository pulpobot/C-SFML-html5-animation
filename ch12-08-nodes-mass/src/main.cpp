#include <iostream>
#include <cmath>
#include <random>
#include "SFML\Graphics.hpp"
#include "Ball.h"

const float minDist = 100.0f;
const float springAmount = 0.001f;

void Spring(Ball &partA, Ball &partB, sf::RenderWindow &window){
    float dx = partB.GetX() - partA.GetX();
    float dy = partB.GetY() - partA.GetY();
    float dist = std::sqrt(dx * dx + dy * dy);
    if(dist < minDist){
        float alpha = 1.0f - dist / minDist;
        std::vector<sf::Vertex> line;
        line.emplace_back(sf::Vertex(sf::Vector2f(partA.GetX(), partA.GetY()), sf::Color(255,255,255,255 * alpha)));
        line.emplace_back(sf::Vertex(sf::Vector2f(partB.GetX(), partB.GetY()), sf::Color(255,255,255,255 * alpha)));
        window.draw(&line[0], line.size(), sf::LinesStrip);
        float ax = dx * springAmount;
        float ay = dy * springAmount;
        partA.vx += ax / partA.mass;
        partA.vy += ay / partA.mass;
        partB.vx -= ax / partB.mass;
        partB.vy -= ay / partB.mass;
    }
}

sf::Vector2f Rotate(float x, float y, float sin, float cos, bool reverse) {
    sf::Vector2f result;
    result.x = (reverse) ? (x * cos + y * sin) : (x * cos - y * sin);
    result.y = (reverse) ? (y * cos - x * sin) : (y * cos + x * sin);
    return result;
}

void Move(std::vector<Ball> &particles, int i, sf::RenderWindow &window){
    particles[i].Translate(particles[i].vx, particles[i].vy);

    if(particles[i].GetX() - particles[i].shape.getRadius() > window.getSize().x){
        particles[i].SetX(-particles[i].shape.getRadius());
    } else if(particles[i].GetX() + particles[i].shape.getRadius() < 0){
        particles[i].SetX(window.getSize().x + particles[i].shape.getRadius());
    }

    if(particles[i].GetY() - particles[i].shape.getRadius() > window.getSize().y){
        particles[i].SetY(-particles[i].shape.getRadius());
    } else if(particles[i].GetY() + particles[i].shape.getRadius() < 0){
        particles[i].SetY(window.getSize().y + particles[i].shape.getRadius());
    }

    for (int j = i + 1; j < particles.size(); ++j) {
        Spring(particles[i], particles[j], window);
    }
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Nodes Mass", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    std::mt19937 m(std::time(NULL));
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    std::vector<Ball> particles;
    int numParticles = 30;

    for (int j = 0; j < numParticles; ++j) {
        float size = dist(m) * 10 + 2;
        particles.emplace_back(Ball(dist(m) * window.getSize().x, dist(m) * window.getSize().y, size, sf::Color::White));
        particles[j].mass = size;
        particles[j].vx = dist(m) * 6 - 3;
        particles[j].vy = dist(m) * 6 - 3;
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

        window.clear(sf::Color::Black);

        for (int i = 0; i < numParticles; ++i) {
            Move(particles, i, window);
            window.draw(particles[i].shape);
        }

        window.display();
    }
}