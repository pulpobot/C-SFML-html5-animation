#include <iostream>
#include <random>
#include <algorithm>
#include "SFML\Graphics.hpp"
#include "Point3d.h"
#include "Triangle.h"
#include "Utils.h"

float fl = 250,
        vpX = 0,
        vpY = 0;

void Move(Point3d &point, float angleX, float angleY) {
    point.RotateX(angleX);
    point.RotateY(angleY);
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Cylinder", sf::Style::Titlebar | sf::Style::Close,
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

    std::vector <Point3d> points;
    std::vector <Triangle> triangles;
    float angleX = 0;
    float angleY = 0;
    vpX = window.getSize().x / 2.0f;
    vpY = window.getSize().y / 2.0f;

    int numFaces = 20;

    float angle,
            xPos,
            yPos,
            idx;

    for (int k = 0; k < numFaces; ++k) {
        angle = M_PI * 2 / numFaces * k;
        xPos = std::cos(angle) * 200;
        yPos = std::sin(angle) * 200;
        points.emplace_back(Point3d(xPos, yPos, -100));
        points.emplace_back(Point3d(xPos, yPos, 100));
        idx += 2;
    }

    for (int j = 0; j < points.size(); ++j) {
        points[j].SetVanishingPoint(vpX, vpY);
        points[j].SetCenter(0, 0, 200);
    }

    idx = 0;
    for (int l = 0; l < numFaces - 1; ++l) {
        triangles.emplace_back(
                Triangle(points[idx], points[idx + 3], points[idx + 1], Utils::HexColorToSFMLColor("#6666cc")));
        triangles.emplace_back(
                Triangle(points[idx], points[idx + 2], points[idx + 3], Utils::HexColorToSFMLColor("#6666cc")));
        idx += 2;
    }

    triangles.emplace_back(Triangle(points[idx], points[1], points[idx + 1], Utils::HexColorToSFMLColor("#6666cc")));
    triangles.emplace_back(Triangle(points[idx], points[0], points[1], Utils::HexColorToSFMLColor("#6666cc")));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    angleX = (event.mouseMove.y - vpY) * 0.0005;
                    angleY = (event.mouseMove.x - vpX) * 0.0005;
                    break;
            }
        }


        for (int i = 0; i < points.size(); ++i) {
            Move(points[i], angleX, angleY);
        }

        window.clear(sf::Color::White);
        for (int j = 0; j < triangles.size(); ++j) {
            triangles[j].Draw(window);
        }
        window.draw(infoText);
        window.display();
    }
}
