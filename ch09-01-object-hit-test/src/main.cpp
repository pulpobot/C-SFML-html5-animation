#include <iostream>
#include "SFML\Graphics.hpp"
#include "Ball.h"
#include "Utils.h"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Object Hit Test", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Ball ball0((window.getSize().x / 2), (window.getSize().y / 2) - 100, 40, sf::Color::Red);
    Ball ball1((window.getSize().x / 2), window.getSize().y / 2, 40, sf::Color::Red);
    std::vector<sf::Vertex> line;

    sf::Font font;
    if(!font.loadFromFile("res/cour.ttf")){
        std::cerr << "Error loading cout.ttf file" << std::endl;
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(10,10));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    ball0.SetX(event.mouseMove.x);
                    ball0.SetY(event.mouseMove.y);
                    break;
            }
        }

        if(Utils::Intersects(ball0.GetBounds(), ball1.GetBounds()))
            text.setString("Hit");
        else
            text.setString("");

        window.clear(sf::Color::White);
        line.clear();
        line.emplace_back(sf::Vertex(sf::Vector2f(ball0.GetBounds().left, ball0.GetBounds().top), sf::Color::Black));
        line.emplace_back(sf::Vertex(sf::Vector2f(ball0.GetBounds().left + ball0.GetBounds().width, ball0.GetBounds().top), sf::Color::Black));
        line.emplace_back(sf::Vertex(sf::Vector2f(ball0.GetBounds().left + ball0.GetBounds().width, ball0.GetBounds().top + ball0.GetBounds().height), sf::Color::Black));
        line.emplace_back(sf::Vertex(sf::Vector2f(ball0.GetBounds().left, ball0.GetBounds().top + ball0.GetBounds().height), sf::Color::Black));
        line.emplace_back(sf::Vertex(sf::Vector2f(ball0.GetBounds().left, ball0.GetBounds().top), sf::Color::Black));
        window.draw(&line[0], line.size(), sf::PrimitiveType::LinesStrip);

        line.clear();
        line.emplace_back(sf::Vertex(sf::Vector2f(ball1.GetBounds().left, ball1.GetBounds().top), sf::Color::Black));
        line.emplace_back(sf::Vertex(sf::Vector2f(ball1.GetBounds().left + ball1.GetBounds().width, ball1.GetBounds().top), sf::Color::Black));
        line.emplace_back(sf::Vertex(sf::Vector2f(ball1.GetBounds().left + ball1.GetBounds().width, ball1.GetBounds().top + ball1.GetBounds().height), sf::Color::Black));
        line.emplace_back(sf::Vertex(sf::Vector2f(ball1.GetBounds().left, ball1.GetBounds().top + ball1.GetBounds().height), sf::Color::Black));
        line.emplace_back(sf::Vertex(sf::Vector2f(ball1.GetBounds().left, ball1.GetBounds().top), sf::Color::Black));
        window.draw(&line[0], line.size(), sf::PrimitiveType::LinesStrip);

        window.draw(ball0.shape);
        window.draw(ball1.shape);
        window.draw(text);

        window.display();
    }
}