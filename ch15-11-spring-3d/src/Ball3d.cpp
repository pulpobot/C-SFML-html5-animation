#include "SFML\Graphics.hpp"
#include "Ball3d.h"

Ball3d::Ball3d(float x, float y, float z, float radius, sf::Color color) {
    shape = sf::CircleShape(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
    shape.setPosition(x, y);
    zPos = z;
    shape.setOutlineThickness(-1);
    shape.setOutlineColor(sf::Color::Black);
    vx = 0;
    vy = 0;
    vz = 0;
}

Ball3d::~Ball3d() {
}

void Ball3d::SetPosition(float x, float y, float z) {
    shape.setPosition(sf::Vector2f(x, y));
    zPos = z;
}

void Ball3d::SetX(float x) {
    shape.setPosition(sf::Vector2f(x, shape.getPosition().y));
}

void Ball3d::SetY(float y) {
    shape.setPosition(sf::Vector2f(shape.getPosition().x, y));
}

void Ball3d::SetZ(float z) {
    zPos = z;
}

float Ball3d::GetX() {
    return shape.getPosition().x;
}

float Ball3d::GetY() {
    return shape.getPosition().y;
}

float Ball3d::GetZ() {
    return zPos;
}

void Ball3d::Translate(float x, float y) {
    shape.setPosition(sf::Vector2f(shape.getPosition().x + x, shape.getPosition().y + y));
}

void Ball3d::SetRotation(float angle) {
    shape.setRotation(angle);
}

void Ball3d::Rotate(float angle) {
    shape.setRotation(angle + shape.getRotation());
}

void Ball3d::Draw(sf::RenderWindow &renderWindow) {
    if(visible)
        renderWindow.draw(shape);
}

sf::FloatRect Ball3d::GetBounds()
{
    return shape.getGlobalBounds();
}
