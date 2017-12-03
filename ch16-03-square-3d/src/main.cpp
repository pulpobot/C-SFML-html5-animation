#include <iostream>
#include <random>
#include <algorithm>
#include "SFML\Graphics.hpp"
#include "Point3d.h"

float fl = 250,
        vpX = 0,
        vpY = 0;

void Move(Point3d &point, float angleX, float angleY, std::vector<sf::Vertex> &lines) {
    point.RotateX(angleX);
    point.RotateY(angleY);

    lines.emplace_back(sf::Vertex(sf::Vector2f(point.GetScreenX(), point.GetScreenY()), sf::Color::Black));
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Square 3D", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("res/cour.ttf")) {
        std::cerr << "Error loading cour.ttf file" << std::endl;
        return -1;
    }

    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(10);
    infoText.setFillColor(sf::Color::Black);
    infoText.setPosition(sf::Vector2f(5, window.getSize().y - 20));
    infoText.setString("Move mouse on window.");

    std::mt19937 m(time(NULL));
    std::uniform_real_distribution<float> t(0.0f, 1.0f);

    std::vector<Point3d> points;
    float angleX = 0;
    float angleY = 0;
    vpX = window.getSize().x / 2.0f;
    vpY = window.getSize().y / 2.0f;

    points.emplace_back(Point3d(-100, -100, 100));
    points.emplace_back(Point3d(100, -100, 100));
    points.emplace_back(Point3d(100, 100, 100));
    points.emplace_back(Point3d(-100, 100, 100));

    for (int j = 0; j < points.size(); ++j) {
        points[j].SetVanishingPoint(vpX, vpY);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    angleX = (event.mouseMove.y - vpY) * 0.001;
                    angleY = (event.mouseMove.x - vpX) * 0.001;
                    break;
            }
        }

        std::vector<sf::Vertex> lines;

        for (int i = 0; i < points.size(); ++i) {
            Move(points[i], angleX, angleY, lines);
        }

        lines.emplace_back(sf::Vertex(sf::Vector2f(points[0].GetScreenX(), points[0].GetScreenY()), sf::Color::Black));

        window.clear(sf::Color::White);
        window.draw(&lines[0], lines.size(), sf::LinesStrip);
        window.draw(infoText);
        window.display();
    }

}
