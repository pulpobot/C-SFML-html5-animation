#include "Ball.h"
#include "SFML\Graphics.hpp"

Ball::Ball(float x, float y, float radius, sf::Color color) {
    shape = sf::CircleShape(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
    shape.setPosition(x, y);
    shape.setOutlineThickness(-2);
    shape.setOutlineColor(sf::Color::Black);
    vx = 0;
    vy = 0;
}


Ball::~Ball() {
}

void Ball::SetPosition(float x, float y) {
    shape.setPosition(sf::Vector2f(x, y));
}

void Ball::SetX(float x) {
    shape.setPosition(sf::Vector2f(x, shape.getPosition().y));
}

void Ball::SetY(float y) {
    shape.setPosition(sf::Vector2f(shape.getPosition().x, y));
}

float Ball::GetX() {
    return shape.getPosition().x;
}

float Ball::GetY() {
    return shape.getPosition().y;
}

void Ball::Translate(float x, float y) {
    shape.setPosition(sf::Vector2f(shape.getPosition().x + x, shape.getPosition().y + y));
}

void Ball::SetRotation(float angle) {
    shape.setRotation(angle);
}

void Ball::Rotate(float angle) {
    shape.setRotation(angle + shape.getRotation());
}

void Ball::Draw(sf::RenderWindow &renderWindow, float gravity) {
    vy += gravity;
    Translate(vx, vy);
    renderWindow.draw(shape);
}

sf::FloatRect Ball::GetBounds()
{
    return shape.getGlobalBounds();
}
