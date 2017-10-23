#include "Line.h"

Line::Line(float x, float y, float length, sf::Color color) {
    shape = sf::RectangleShape(sf::Vector2f(length, 2));
    shape.setFillColor(color);
    shape.setOrigin(length / 2, 1);
    shape.setPosition(x + length / 2, y);
    vx = 0;
    vy = 0;
}

Line::~Line() {
}

void Line::SetPosition(float x, float y) {
    shape.setPosition(sf::Vector2f(x, y));
}

void Line::SetX(float x) {
    shape.setPosition(sf::Vector2f(x, shape.getPosition().y));
}

void Line::SetY(float y) {
    shape.setPosition(sf::Vector2f(shape.getPosition().x, y));
}

float Line::GetX() {
    return shape.getPosition().x;
}

float Line::GetY() {
    return shape.getPosition().y;
}

void Line::Translate(float x, float y) {
    shape.setPosition(sf::Vector2f(shape.getPosition().x + x, shape.getPosition().y + y));
}

void Line::SetRotation(float angle) {
    shape.setRotation(angle);
}

void Line::Rotate(float angle) {
    shape.rotate(angle);
}

float Line::Rotation() {
    shape.getRotation();
}

void Line::Draw(sf::RenderWindow &renderWindow, float gravity) {
    vy += gravity;
    Translate(vx, vy);
    renderWindow.draw(shape);
}

sf::FloatRect Line::GetBounds() {
    return shape.getGlobalBounds();
}
