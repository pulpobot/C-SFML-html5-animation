#include <iostream>
#include <random>
#include "SFML\Graphics.hpp"
#include "Utils.h"
#include "Box.h"

const float GRAVITY = 0.3f;

std::vector<Box> boxes;

Box *CreateBox(sf::RenderWindow &window) {
    //it gets unstable after 256 boxes
    if (boxes.size() >= 256) return nullptr;

    std::mt19937 mt(time(NULL));
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    boxes.emplace_back(
            Box(window.getSize().x * dist(mt), 0, dist(mt) * 40 + 10, dist(mt) * 40 + 10,
                sf::Color::Red));

    return &boxes.back();
}

void DrawBox(Box *&activeBox, Box &box, sf::RenderWindow &window) {
    if (activeBox != nullptr) {
        if (activeBox != &box && Utils::Intersects((*activeBox).GetBounds(), box.GetBounds())) {
            (*activeBox).SetY(box.GetBounds().top - (*activeBox).GetBounds().height / 2);
            activeBox = CreateBox(window);
        }
    }
    window.draw(box.shape);
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Boxes", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Box *activeBox = CreateBox(window);

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

        if (activeBox != nullptr) {
            (*activeBox).vy += GRAVITY;
            (*activeBox).Translate((*activeBox).vx, (*activeBox).vy);

            if ((*activeBox).GetBounds().top + (*activeBox).GetBounds().height >= window.getSize().y) {
                (*activeBox).SetY(window.getSize().y - (*activeBox).GetBounds().height / 2);
                activeBox = CreateBox(window);
            }
        }

        for (int i = 0; i < boxes.size(); ++i) {
            DrawBox(activeBox, boxes[i], window);
        }

        window.display();
    }
}