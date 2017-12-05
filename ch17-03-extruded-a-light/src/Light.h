#pragma once
#include "SFML\Graphics.hpp"
#include <string>

class Light
{
public:
	Light(float px = -100, float py = -100, float pz = -100, float b = 1);
	~Light();
	float x;
	float y;
	float z;
    float brightness = 1;
	void SetBrightness(float b);
};