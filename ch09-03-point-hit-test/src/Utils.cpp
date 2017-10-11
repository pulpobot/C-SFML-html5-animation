#include "Utils.h"

void Utils::Bezier::QuadraticBezierCurve(const sf::Vector2f &p0, sf::Vector2f &p1, sf::Vector2f &p2, int segments,
                                         std::vector<sf::Vector2f> &curvePoints, bool throughControlPoint) {
    //If there are any segments required
    if (segments <= 0)
        return;

    //Quadratic Bezier Curve Math Formula: (1 - t)*((1-t)*p0 + t*p1) + t*((1-t)*p1 + t*p2);
    curvePoints.clear();
    float stepIncreasement = 1.0f / segments;
    float t = 0.0f;
    float px = 0.0f;
    float py = 0.0f;

    if (throughControlPoint) {
        p1.x = p1.x * 2 - (p0.x + p2.x) / 2;
        p1.y = p1.y * 2 - (p0.y + p2.y) / 2;
    }

    for (int i = 0; i <= segments; i++) {
        px = (1.0f - t) * ((1.0f - t) * p0.x + t * p1.x) + t * ((1.0f - t) * p1.x + t * p2.x);
        py = (1.0f - t) * ((1.0f - t) * p0.y + t * p1.y) + t * ((1.0f - t) * p1.y + t * p2.y);
        curvePoints.push_back(sf::Vector2f(px, py));
        t += stepIncreasement;
    }
}

void Utils::Bezier::QuadraticBezierCurve(const sf::Vector2f &p0, sf::Vector2f &p1, sf::Vector2f &p2, int segments,
                                         std::vector<sf::Vertex> &curvePoints, sf::Color lineColor,
                                         bool throughControlPoint) {
    //If there are any segments required
    if (segments <= 0)
        return;

    //Quadratic Bezier Curve Math Formula: (1 - t)*((1-t)*p0 + t*p1) + t*((1-t)*p1 + t*p2);
    curvePoints.clear();
    float stepIncreasement = 1.0f / segments;
    float t = 0;
    float px = 0;
    float py = 0;

    if (throughControlPoint) {
        p1.x = p1.x * 2 - (p0.x + p2.x) / 2;
        p1.y = p1.y * 2 - (p0.y + p2.y) / 2;
    }

    //Add points based on control point's position
    for (int i = 0; i <= segments; i++) {
        px = (1.0f - t) * ((1.0f - t) * p0.x + t * p1.x) + t * ((1.0f - t) * p1.x + t * p2.x);
        py = (1.0f - t) * ((1.0f - t) * p0.y + t * p1.y) + t * ((1.0f - t) * p1.y + t * p2.y);
        curvePoints.push_back(sf::Vertex(sf::Vector2f(px, py), lineColor));
        t += stepIncreasement;
    }
}

///Same as QuadraticBezierCurve, but it doesn't clear the array before pushing vertex
void Utils::Bezier::AccumulativeQuadraticBezierCurve(const sf::Vector2f &p0, sf::Vector2f &p1, sf::Vector2f &p2,
                                                     int segments, std::vector<sf::Vertex> &curvePoints,
                                                     sf::Color lineColor, bool throughControlPoint) {
    //If there are any segments required
    if (segments <= 0)
        return;

    //Quadratic Bezier Curve Math Formula: (1 - t)*((1-t)*p0 + t*p1) + t*((1-t)*p1 + t*p2);
    float stepIncreasement = 1.0f / segments;
    float t = 0;
    float px = 0;
    float py = 0;

    if (throughControlPoint) {
        p1.x = p1.x * 2 - (p0.x + p2.x) / 2;
        p1.y = p1.y * 2 - (p0.y + p2.y) / 2;
    }

    //Add points based on control point's position
    for (int i = 0; i <= segments; i++) {
        px = (1.0f - t) * ((1.0f - t) * p0.x + t * p1.x) + t * ((1.0f - t) * p1.x + t * p2.x);
        py = (1.0f - t) * ((1.0f - t) * p0.y + t * p1.y) + t * ((1.0f - t) * p1.y + t * p2.y);
        curvePoints.push_back(sf::Vertex(sf::Vector2f(px, py), lineColor));
        t += stepIncreasement;
    }
}

bool ::Utils::ContainsPoint(sf::FloatRect rect, float x, float y) {
    //SFML already has a "contains" function inside FloatRect class
    //return rect.contains(x,y);
    return !(x < rect.left || x > rect.left + rect.width ||
            y < rect.top || y > rect.top + rect.height);
}

bool ::Utils::Intersects(sf::FloatRect rectA, sf::FloatRect rectB) {
    //SFML already has an "intersects" function inside FloatRect class
    //return rectA.intersects(rectB);
    return !(rectA.left + rectA.width < rectB.left ||
            rectB.left + rectB.width < rectA.left ||
            rectA.top + rectA.width < rectB.top ||
            rectB.top + rectB.width < rectA.top );
}


