#pragma once
#include "SFML\Graphics.hpp"
#include <string>
#include <random>

class Tree
{
public:
	Tree(float x, float y, float z, std::mt19937 &m, std::uniform_real_distribution<float> &t);
	~Tree();

	sf::ConvexShape mainBranch;
    sf::ConvexShape lowerBranch;
    sf::ConvexShape upperBranch;
	float vx;
	float vy;
	float vz;
    float xPos;
    float yPos;
    float zPos;
	float branchHalfThickness = 0.5f;
    bool visible = true;
	///Overrides current position
	void SetPosition(float x, float y, float z);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	float GetX();
	float GetY();
	float GetZ();
	///Increase current position by x and y values
	void Translate(float x, float y);
	///Overrides current rotation (in degrees)
	void SetRotation(float angle);
	///Increase current rotation by an anglee (in degrees)
	void Rotate(float angle);
    void SetScale(float scale);
    void Alpha(float alpha);
    void Draw(sf::RenderWindow &renderWindow);
	sf::FloatRect GetBounds();
};

