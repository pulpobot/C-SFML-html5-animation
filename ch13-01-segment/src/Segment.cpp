#include <cmath>
#include "Segment.h"
#include "Utils.h"

Segment::Segment(float width, float height, sf::Color color) {
    this->width = width;
    this->height = height;

    shape = sf::ConvexShape();
    float h = height;
    float d = width + h; //top right diagonal
    float cr = height / 2; //corner radius
    int amountOfPoint = 2;
    std::vector<sf::Vector2f> upperRightCorner;
    sf::Vector2f initPoint = sf::Vector2f(d - 2 * cr, -cr);
    sf::Vector2f controlPoint = sf::Vector2f(-cr + d, -cr);
    sf::Vector2f endPoint = sf::Vector2f(-cr + d, 0);
    Utils::Bezier::QuadraticBezierCurve(initPoint, controlPoint, endPoint, 10, upperRightCorner, false);
    amountOfPoint += upperRightCorner.size();

    std::vector<sf::Vector2f> lowerRightCorner;
    initPoint = sf::Vector2f(-cr + d, h - 2 * cr);
    controlPoint = sf::Vector2f(-cr + d, -cr + h);
    endPoint = sf::Vector2f(d - 2 * cr, -cr + h);
    Utils::Bezier::QuadraticBezierCurve(initPoint, controlPoint, endPoint, 10, lowerRightCorner, false);
    amountOfPoint += lowerRightCorner.size();

    std::vector<sf::Vector2f> lowerLeftCorner;
    initPoint = sf::Vector2f(0, -cr + h);
    controlPoint = sf::Vector2f(-cr, -cr + h);
    endPoint = sf::Vector2f(-cr, h - 2 * cr);
    Utils::Bezier::QuadraticBezierCurve(initPoint, controlPoint, endPoint, 10, lowerLeftCorner, false);
    amountOfPoint += lowerLeftCorner.size();

    std::vector<sf::Vector2f> upperLeftCorner;
    initPoint = sf::Vector2f(-cr, 0);
    controlPoint = sf::Vector2f(-cr, -cr);
    endPoint = sf::Vector2f(0, -cr);
    Utils::Bezier::QuadraticBezierCurve(initPoint, controlPoint, endPoint, 10, upperLeftCorner, false);
    amountOfPoint += upperLeftCorner.size();

    shape.setPointCount(amountOfPoint);
    shape.setPoint(0, sf::Vector2f(0, -cr));
    int i = 1;
    for (int j = 0; j < upperRightCorner.size(); ++j) {
        shape.setPoint(i, upperRightCorner[j]);
        i++;
    }

    for (int j = 0; j < lowerRightCorner.size(); ++j) {
        shape.setPoint(i, lowerRightCorner[j]);
        i++;
    }

    shape.setPoint(i, sf::Vector2f(0, -cr + h));

    for (int j = 0; j < lowerLeftCorner.size(); ++j) {
        shape.setPoint(i, lowerLeftCorner[j]);
        i++;
    }

    for (int j = 0; j < upperLeftCorner.size(); ++j) {
        shape.setPoint(i, upperLeftCorner[j]);
        i++;
    }

    shape.setPoint(i, sf::Vector2f(0, -cr));

    //Create the 2 "pins"
    leftPin = sf::CircleShape(1, 10);
    leftPin.setFillColor(sf::Color::White);
    leftPin.setOutlineColor(sf::Color::Black);
    leftPin.setOutlineThickness(1.5f);
    rightPin = sf::CircleShape(1, 10);
    rightPin.setFillColor(sf::Color::White);
    rightPin.setOutlineColor(sf::Color::Black);
    rightPin.setOutlineThickness(1.5f);
    leftPin.setOrigin(1.25f,1.25f);
    leftPin.setPosition(shape.getPosition().x, shape.getPosition().y);
    rightPin.setOrigin(1.25f,1.25f);
    rightPin.setPosition(shape.getPosition().x + width, shape.getPosition().y);

    shape.setFillColor(color);
    shape.setOutlineThickness(-1);
    shape.setOutlineColor(sf::Color::Black);
    vx = 0;
    vy = 0;
}


Segment::~Segment() {
}

void Segment::SetPosition(sf::Vector2f pos) {
    shape.setPosition(pos);
    UpdatePinsPosition();
}

void Segment::SetPosition(float x, float y) {
    SetPosition(sf::Vector2f(x, y));
}


void Segment::SetX(float x) {
    shape.setPosition(sf::Vector2f(x, shape.getPosition().y));
    UpdatePinsPosition();
}

void Segment::SetY(float y) {
    shape.setPosition(sf::Vector2f(shape.getPosition().x, y));
    UpdatePinsPosition();
}

float Segment::GetX() {
    return shape.getPosition().x;
}

float Segment::GetY() {
    return shape.getPosition().y;
}

void Segment::Translate(float x, float y) {
    shape.setPosition(sf::Vector2f(shape.getPosition().x + x, shape.getPosition().y + y));
    UpdatePinsPosition();
}

void Segment::SetRotation(float angle) {
    shape.setRotation(angle);
    UpdatePinsPosition();
}

void Segment::Rotate(float angle) {
    shape.setRotation(angle + shape.getRotation());
    UpdatePinsPosition();
}

void Segment::Draw(sf::RenderWindow &renderWindow) {
    renderWindow.draw(shape);
    renderWindow.draw(leftPin);
    renderWindow.draw(rightPin);
}

void Segment::UpdatePinsPosition(){
    leftPin.setPosition(shape.getPosition().x, shape.getPosition().y);
    rightPin.setPosition(GetPin());
}

sf::Vector2f Segment::GetPin(){
    float x = shape.getPosition().x + std::cos(shape.getRotation() * M_PI / 180) * this->width;
    float y = shape.getPosition().y + std::sin(shape.getRotation() * M_PI / 180) * this->width;
    return sf::Vector2f(x, y);
}

sf::FloatRect Segment::GetBounds() {
    return shape.getGlobalBounds();
}
