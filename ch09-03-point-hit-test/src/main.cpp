#include <iostream>
#include "SFML\Graphics.hpp"
#include "Utils.h"
#include "Ball.h"

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Point Hit Test", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    Ball ball(window.getSize().x / 2, window.getSize().y / 2, 40, sf::Color::Red);
    sf::Font font;
    if(!font.loadFromFile("res/cour.ttf")){
        std::cerr << "Error loading cout.ttf file" << std::endl;
        return -1;
    }

    sf::Text hitText;
    hitText.setFont(font);
    hitText.setCharacterSize(15);
    hitText.setFillColor(sf::Color::Black);
    hitText.setPosition(sf::Vector2f(10,10));

    window.clear(sf::Color::White);
    std::vector<sf::Vertex> bounds;
    bounds.emplace_back(sf::Vertex(sf::Vector2f(ball.GetBounds().top, ball.GetBounds().left), sf::Color::Black));
    bounds.emplace_back(sf::Vertex(sf::Vector2f(ball.GetBounds().top, ball.GetBounds().left + ball.GetBounds().width), sf::Color::Black));
    bounds.emplace_back(sf::Vertex(sf::Vector2f(ball.GetBounds().top + ball.GetBounds().height, ball.GetBounds().left + ball.GetBounds().width), sf::Color::Black));
    bounds.emplace_back(sf::Vertex(sf::Vector2f(ball.GetBounds().top + ball.GetBounds().height, ball.GetBounds().left), sf::Color::Black));
    bounds.emplace_back(sf::Vertex(sf::Vector2f(ball.GetBounds().top, ball.GetBounds().left), sf::Color::Black));

    window.draw(&bounds[0], bounds.size(), sf::PrimitiveType::LinesStrip);
    window.draw(ball.shape);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    if(Utils::ContainsPoint(ball.GetBounds(), event.mouseMove.x, event.mouseMove.y))
                        hitText.setString("Hit");
                    else
                        hitText.setString("");
            }
        }
        window.clear(sf::Color::White);
        window.draw(hitText);
        window.draw(&bounds[0], bounds.size(), sf::PrimitiveType::LinesStrip);
        window.draw(ball.shape);
        window.display();
    }
}