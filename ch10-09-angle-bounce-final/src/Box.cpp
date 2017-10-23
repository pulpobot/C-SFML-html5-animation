#include "Box.h"
#include "SFML\Graphics.hpp"

Box::Box(float x, float y, sf::Vector2f size, sf::Color color) {
    shape = sf::RectangleShape(size);
    shape.setFillColor(color);
    shape.setOrigin(size.x / 2, size.y / 2);
    shape.setPosition(x, y);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);
    vx = 0;
    vy = 0;
}


Box::~Box() {
}

void Box::SetPosition(float x, float y) {
    shape.setPosition(sf::Vector2f(x, y));
}

void Box::SetX(float x) {
    shape.setPosition(sf::Vector2f(x, shape.getPosition().y));
}

void Box::SetY(float y) {
    shape.setPosition(sf::Vector2f(shape.getPosition().x, y));
}

float Box::GetX() {
    return shape.getPosition().x;
}

float Box::GetY() {
    return shape.getPosition().y;
}

void Box::Translate(float x, float y) {
    shape.setPosition(sf::Vector2f(shape.getPosition().x + x, shape.getPosition().y + y));
}

void Box::SetRotation(float angle) {
    shape.setRotation(angle);
}

void Box::Rotate(float angle) {
    shape.setRotation(angle + shape.getRotation());
}

void Box::Draw(sf::RenderWindow &renderWindow, float gravity) {
    vy += gravity;
    Translate(vx, vy);
    renderWindow.draw(shape);
}

sf::FloatRect Box::GetBounds()
{
    return shape.getGlobalBounds();
}
