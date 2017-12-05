#include <iostream>
#include "SFML\Graphics.hpp"
#include "Triangle.h"
#include "math.h"

Triangle::Triangle(Point3d &a, Point3d &b, Point3d &c, sf::Color color) {
    pointA = &a;
    pointB = &b;
    pointC = &c;
    fillColor = sf::Color(color.r, color.g, color.b, 255 * alpha);
    lineColor = color;
}

Triangle::~Triangle() {
}

void Triangle::Draw(sf::RenderWindow &window) {

    if (IsBackface()) return;

    sf::VertexArray triangleShape(sf::PrimitiveType::Triangles, 3);
    sf::Color adjustedColor = GetAdjustedColor();
    triangleShape[0] = sf::Vertex(sf::Vector2f(pointA->GetScreenX(), pointA->GetScreenY()), adjustedColor);
    triangleShape[1] = sf::Vertex(sf::Vector2f(pointB->GetScreenX(), pointB->GetScreenY()), adjustedColor);
    triangleShape[2] = sf::Vertex(sf::Vector2f(pointC->GetScreenX(), pointC->GetScreenY()), adjustedColor);

    window.draw(triangleShape);

    if (lineWidth > 0) {
        std::vector<sf::Vertex> outline;
        outline.emplace_back(sf::Vertex(sf::Vector2f(pointA->GetScreenX(), pointA->GetScreenY()), lineColor));
        outline.emplace_back(sf::Vertex(sf::Vector2f(pointB->GetScreenX(), pointB->GetScreenY()), lineColor));
        outline.emplace_back(sf::Vertex(sf::Vector2f(pointC->GetScreenX(), pointC->GetScreenY()), lineColor));

        window.draw(&outline[0], outline.size(), sf::LinesStrip);
    }
}

bool Triangle::IsBackface() {
    float cax = pointC->GetScreenX() - pointA->GetScreenX(),
            cay = pointC->GetScreenY() - pointA->GetScreenY(),
            bcx = pointB->GetScreenX() - pointC->GetScreenX(),
            bcy = pointB->GetScreenY() - pointC->GetScreenY();

    return (cax * bcy > cay * bcx);
}

float Triangle::GetDepth() const {
    return std::fminf(std::fminf(pointA->z, pointB->z), pointC->z);
}

sf::Color Triangle::GetAdjustedColor() {
    sf::Color adjustedColor = fillColor;
    float lightFactor = GetLightFactor();
    adjustedColor.r *= lightFactor;
    adjustedColor.g *= lightFactor;
    adjustedColor.b *= lightFactor;

    return adjustedColor;
}

float Triangle::GetLightFactor() {
    sf::Vector3f ab;
    ab.x = pointA->x - pointB->x;
    ab.y = pointA->y - pointB->y;
    ab.z = pointA->z - pointB->z;

    sf::Vector3f bc;
    bc.x = pointB->x - pointC->x;
    bc.y = pointB->y - pointC->y;
    bc.z = pointB->z - pointC->z;

    sf::Vector3f norm;
    norm.x = (ab.y * bc.z) - (ab.z * bc.y);
    norm.y = -((ab.x * bc.z) - (ab.z * bc.x));
    norm.z = (ab.x * bc.y) - (ab.y * bc.x);

    float dotProd = norm.x * light->x +
                    norm.y * light->y +
                    norm.z * light->z;

    float normMag = std::sqrt(norm.x * norm.x +
                              norm.y * norm.y +
                              norm.z * norm.z);

    float lightMag = std::sqrt(light->x * light->x +
                               light->y * light->y +
                               light->z * light->z);

    return (std::acos(dotProd / (normMag * lightMag)) / M_PI) * light->brightness;
}

