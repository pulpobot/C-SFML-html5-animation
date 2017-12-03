#include "SFML\Graphics.hpp"
#include "Point3d.h"
#include "math.h"

Point3d::Point3d(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
    fl = 250;
    vpX = 0;
    vpY = 0;
    cX = 0;
    cY = 0;
    cZ = 0;
}

Point3d::~Point3d() {
}

void Point3d::SetCenter(float x, float y, float z){
    cX = x;
    cY = y;
    cZ = z;
}
void Point3d::SetVanishingPoint(float x, float y){
    vpX = x;
    vpY = y;
}
void Point3d::RotateX(float angle){
    float cos = std::cos(angle),
            sin = std::sin(angle),
            y1 = y * cos - z * sin,
            z1 = z * cos + y * sin;

    y = y1;
    z = z1;
}
void Point3d::RotateY(float angle){
    float cos = std::cos(angle),
            sin = std::sin(angle),
            x1 = x * cos - z * sin,
            z1 = z * cos + x * sin;

    x = x1;
    z = z1;
}
void Point3d::RotateZ(float angle){
    float cos = std::cos(angle),
            sin = std::sin(angle),
            x1 = x * cos - y * sin,
            y1 = y * cos + x * sin;

    x = x1;
    y = y1;
}
float Point3d::GetScreenX(){
    float scale = fl / (fl + z + cZ);
    return vpX + (cX + x) * scale;
}
float Point3d::GetScreenY(){
    float scale = fl / (fl + z + cZ);
    return vpY + (cY + y) * scale;
}