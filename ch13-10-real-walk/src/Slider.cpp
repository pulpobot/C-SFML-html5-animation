#include <cmath>
#include <iostream>
#include <algorithm>
#include "Slider.h"
#include "Utils.h"

Slider::Slider(float min, float max, float value) {
    this->min = min;
    this->max = max;
    this->value = value;
    backX = this->width / 2 - this->backWidth / 2;

    background = sf::RectangleShape(sf::Vector2f(backWidth, height));
    background.setOrigin(backWidth / 2, 0);
    background.setFillColor(backColor);
    handle.setOutlineColor(backBorderColor);
    handle.setOutlineThickness(-2);

    handle = sf::RectangleShape(sf::Vector2f(width, handleHeight));
    handle.setOrigin(width / 2, 0);
    handle.setPosition(0, handleY);
    handle.setFillColor(handleColor);
    handle.setOutlineColor(handleBorderColor);
    handle.setOutlineThickness(-1);

    UpdatePosition();
    yBounds = background.getPosition().y;
}


Slider::~Slider() {
}

void Slider::SetPosition(float x, float y) {
    background.setPosition(sf::Vector2f(x, y));
}

void Slider::SetX(float x) {
    background.setPosition(sf::Vector2f(x, background.getPosition().y));
    handle.setPosition(x, handleY + background.getPosition().y);
}

void Slider::SetY(float y) {
    background.setPosition(sf::Vector2f(background.getPosition().x, y));
    handle.setPosition(background.getPosition().x, handleY + background.getPosition().y);
    yBounds = background.getPosition().y;
}

float Slider::GetX() {
    return background.getPosition().x;
}

float Slider::GetY() {
    return background.getPosition().y;
}

void Slider::Translate(float x, float y) {
    background.setPosition(sf::Vector2f(background.getPosition().x + x, background.getPosition().y + y));
    handle.setPosition(background.getPosition().x, handleY + background.getPosition().y);
}

void Slider::Draw(sf::RenderWindow &renderWindow) {
    renderWindow.draw(background);
    renderWindow.draw(handle);
}

void Slider::UpdateValue(){
    float old_value = value;
    float handleRange = height - handleHeight;
    float valueRange = max - min;

    value = (handleRange - handleY) / handleRange * valueRange + min;
    if(onChange != nullptr && value != old_value)
        onChange(this);
}

void Slider::CaptureMouse(const sf::Vector2f mousePos){
    if(Utils::ContainsPoint(GetHandleRect(), mousePos.x, mousePos.y)){
        isBeingDragged = true;
    }
}

void Slider::OnMouseRelease(){
    isBeingDragged = false;
}

void Slider::OnMouseMove(const sf::Vector2f mousePos){
    if(isBeingDragged){
        float pos_y = mousePos.y - yBounds;
        handleY = std::fmin(height - handleHeight, std::fmax(pos_y, 0));
        UpdateValue();
    }
}

void Slider::UpdatePosition() {
    float handleRange = height - handleHeight;
    float valueRange = max - min;
    handleY = handleRange - ((value - min) / valueRange) * handleRange;
};

sf::FloatRect Slider::GetHandleRect() {
    return handle.getGlobalBounds();
}
