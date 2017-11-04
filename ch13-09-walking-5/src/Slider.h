#pragma once
#include "SFML\Graphics.hpp"
#include <string>

class Slider
{
public:
	Slider(float min = 0, float max = 100, float value = 100);
	~Slider();
    sf::RectangleShape background;
    sf::RectangleShape handle;

    std::string id;
    float min = 0;
    float max= 0;
    float value = 1;
    float width = 16;
    float height = 100;
    sf::Color backColor = sf::Color(204,204,204,255);
    sf::Color backBorderColor = sf::Color(153,153,153,255);
    float backWidth = 4;
    float backX;
    sf::Color handleColor = sf::Color(238,238,238,255);
    sf::Color handleBorderColor = sf::Color(204,204,204,255);
    float handleHeight = 6;
    float handleY = 0;
    float yBounds;
    bool isBeingDragged = false;
    void (*onChange)(Slider * slider);
	///Overrides current position
	void SetPosition(float x, float y);
	void SetX(float x);
	void SetY(float y);
	float GetX();
	float GetY();
	///Increase current position by x and y values
	void Translate(float x, float y);
    void Draw(sf::RenderWindow &renderWindow);
    void UpdateValue();
    void UpdatePosition();
    void CaptureMouse(sf::Vector2f mousePos);
    void OnMouseRelease();
    void OnMouseMove(sf::Vector2f mousePos);
    sf::FloatRect GetHandleRect();
};

