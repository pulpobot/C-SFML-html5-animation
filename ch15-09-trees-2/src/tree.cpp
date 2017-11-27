#include "SFML\Graphics.hpp"
#include "Tree.h"
#include <iostream>

Tree::Tree(float x, float y, float z, std::mt19937 &m, std::uniform_real_distribution<float> &t) {
    mainBranch = sf::ConvexShape(4);
    mainBranch.setFillColor(sf::Color::White);
    mainBranch.setPosition(x, y);
    lowerBranch = sf::ConvexShape(4);
    lowerBranch.setFillColor(sf::Color::White);
    lowerBranch.setPosition(x, y);
    upperBranch = sf::ConvexShape(4);
    upperBranch.setFillColor(sf::Color::White);
    upperBranch.setPosition(x, y);
    zPos = z;

    float rndValue1 = 0;
    float rndValue2 = 0;
    float rndValue3 = 0;

    //Main Branch
    rndValue1 = -140 - t(m) * 20;
    mainBranch.setPoint(0, sf::Vector2f(branchHalfThickness, 0));
    mainBranch.setPoint(1, sf::Vector2f(-branchHalfThickness, 0));
    mainBranch.setPoint(2, sf::Vector2f(-branchHalfThickness, rndValue1));
    mainBranch.setPoint(3, sf::Vector2f(branchHalfThickness, rndValue1));
    //Branch 1
    rndValue1 = -30 - t(m) * 30;
    rndValue2 = t(m) * 80 - 40;
    rndValue3 = -100 - t(m) * 40;
    lowerBranch.setPoint(0, sf::Vector2f(0, rndValue1 + branchHalfThickness * 2));
    lowerBranch.setPoint(1, sf::Vector2f(rndValue2 - branchHalfThickness, rndValue3 + branchHalfThickness));
    lowerBranch.setPoint(2, sf::Vector2f(rndValue2 + branchHalfThickness, rndValue3 - branchHalfThickness));
    lowerBranch.setPoint(3, sf::Vector2f(0, rndValue1 - branchHalfThickness * 2));

    //Branch 2
    rndValue1 = -60 - t(m) * 40;
    rndValue2 = t(m) * 60 - 30;
    rndValue3 = -110 - t(m) * 20;
    upperBranch.setPoint(0, sf::Vector2f(0, rndValue1 + branchHalfThickness * 2));
    upperBranch.setPoint(1, sf::Vector2f(rndValue2 - branchHalfThickness, rndValue3 + branchHalfThickness));
    upperBranch.setPoint(2, sf::Vector2f(rndValue2 + branchHalfThickness, rndValue3 - branchHalfThickness));
    upperBranch.setPoint(3, sf::Vector2f(0, rndValue1 - branchHalfThickness * 2));


    vx = 0;
    vy = 0;
    vz = 0;
}

Tree::~Tree() {
}

void Tree::SetPosition(float x, float y, float z) {
    mainBranch.setPosition(sf::Vector2f(x, y));
    lowerBranch.setPosition(sf::Vector2f(x, y));
    upperBranch.setPosition(sf::Vector2f(x, y));
    zPos = z;
}

void Tree::SetX(float x) {
    mainBranch.setPosition(sf::Vector2f(x, mainBranch.getPosition().y));
    lowerBranch.setPosition(sf::Vector2f(x, lowerBranch.getPosition().y));
    upperBranch.setPosition(sf::Vector2f(x, upperBranch.getPosition().y));
}

void Tree::SetY(float y) {
    mainBranch.setPosition(sf::Vector2f(mainBranch.getPosition().x, y));
    lowerBranch.setPosition(sf::Vector2f(lowerBranch.getPosition().x, y));
    upperBranch.setPosition(sf::Vector2f(upperBranch.getPosition().x, y));
}

void Tree::SetZ(float z) {
    zPos = z;
}

float Tree::GetX() {
    return mainBranch.getPosition().x;
}

float Tree::GetY() {
    return mainBranch.getPosition().y;
}

float Tree::GetZ() {
    return zPos;
}

void Tree::Translate(float x, float y) {
    mainBranch.setPosition(sf::Vector2f(mainBranch.getPosition().x + x, mainBranch.getPosition().y + y));
    lowerBranch.setPosition(sf::Vector2f(lowerBranch.getPosition().x + x, lowerBranch.getPosition().y + y));
    upperBranch.setPosition(sf::Vector2f(upperBranch.getPosition().x + x, upperBranch.getPosition().y + y));
}

void Tree::SetRotation(float angle) {
    mainBranch.setRotation(angle);
    lowerBranch.setRotation(angle);
    upperBranch.setRotation(angle);
}

void Tree::Rotate(float angle) {
    mainBranch.setRotation(angle + mainBranch.getRotation());
    lowerBranch.setRotation(angle + lowerBranch.getRotation());
    upperBranch.setRotation(angle + upperBranch.getRotation());
}

void Tree::Draw(sf::RenderWindow &renderWindow) {
    if (visible) {
        renderWindow.draw(mainBranch);
        renderWindow.draw(lowerBranch);
        renderWindow.draw(upperBranch);
    }
}

void Tree::SetScale(float scale){
    mainBranch.setScale(sf::Vector2f(scale, scale));
    lowerBranch.setScale(sf::Vector2f(scale, scale));
    upperBranch.setScale(sf::Vector2f(scale, scale));
}

void Tree::Alpha(float alpha){
    sf::Color newColor = mainBranch.getFillColor();
    if(alpha > 1)
        alpha = 1;
    newColor.a = alpha * 255;
    mainBranch.setFillColor(newColor);
    lowerBranch.setFillColor(newColor);
    upperBranch.setFillColor(newColor);
}

sf::FloatRect Tree::GetBounds() {
    return mainBranch.getGlobalBounds();
}
