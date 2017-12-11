#include <iostream>
#include <random>
#include <algorithm>
#include "SFML\Graphics.hpp"
#include "ball3d.h"

float fl = 250,
        vpX = 0,
        vpY = 0;

float * MatrixMultiply(float (&matrixA)[3], float (&matrixB)[3][3]){
    float * result = new float[3];
    result[0] = matrixA[0] * matrixB[0][0] +
                matrixA[1] * matrixB[1][0] +
                matrixA[2] * matrixB[2][0];

    result[1] = matrixA[0] * matrixB[0][1] +
                matrixA[1] * matrixB[1][1] +
                matrixA[2] * matrixB[2][1];

    result[2] = matrixA[0] * matrixB[0][2] +
                matrixA[1] * matrixB[1][2] +
                matrixA[2] * matrixB[2][2];

    return result;
}

void RotateY(Ball3d &ball, float angle) {
    float position[]{ball.xPos, ball.yPos, ball.zPos};
    float cos = std::cos(angle),
            sin = std::sin(angle);

    float xRotMatrix[3][3] = {{cos,  0, sin},
                              {0,    1, 0},
                              {-sin, 0, cos}};

    float * matrixResult = MatrixMultiply(position, xRotMatrix);
    ball.xPos = matrixResult[0];
    ball.yPos = matrixResult[1];
    ball.zPos = matrixResult[2];

    delete[] matrixResult;
}

void RotateX(Ball3d &ball, float angle) {
    float position[]{ball.xPos, ball.yPos, ball.zPos};
    float cos = std::cos(angle),
            sin = std::sin(angle);

    float xRotMatrix[3][3] = {{1, 0, 0},
                              {0, cos, sin},
                              {0, -sin, cos}};

    float * matrixResult = MatrixMultiply(position, xRotMatrix);

    ball.xPos = matrixResult[0];
    ball.yPos = matrixResult[1];
    ball.zPos = matrixResult[2];

    delete[] matrixResult;
}

void SetPerspective(Ball3d &ball) {
    if (ball.zPos > -fl) {
        float scale = fl / (fl + ball.zPos);
        ball.shape.setScale(sf::Vector2f(scale, scale));
        ball.SetX(vpX + ball.xPos * scale);
        ball.SetY(vpY + ball.yPos * scale);
        ball.visible = true;
    } else
        ball.visible = false;
}

bool zSort(const Ball3d &ballA, const Ball3d &ballB) {
    return ballB.zPos < ballA.zPos;
}

void Move(Ball3d &ball, float angleX, float angleY) {
    RotateX(ball, angleX);
    RotateY(ball, angleY);
    SetPerspective(ball);
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Rotate XY", sf::Style::Titlebar | sf::Style::Close,
                            context);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("res/cour.ttf")) {
        std::cerr << "Error loading cour.ttf file" << std::endl;
        return -1;
    }

    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(10);
    infoText.setFillColor(sf::Color::Black);
    infoText.setPosition(sf::Vector2f(5, window.getSize().y - 20));
    infoText.setString("Move mouse on window.");

    std::mt19937 m(time(NULL));
    std::uniform_real_distribution<float> t(0.0f, 1.0f);

    std::vector<Ball3d> balls;
    int numBalls = 50;
    float angleX = 0;
    float angleY = 0;
    vpX = window.getSize().x / 2.0f;
    vpY = window.getSize().y / 2.0f;

    for (int i = 0; i < numBalls; ++i) {
        balls.emplace_back(Ball3d(0, 0, 0, 15, sf::Color::Red));
        balls[i].xPos = t(m) * 200 - 100;
        balls[i].yPos = t(m) * 200 - 100;
        balls[i].zPos = t(m) * 200 - 100;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    angleX = (event.mouseMove.y - vpY) * 0.001;
                    angleY = (event.mouseMove.x - vpX) * 0.001;
                    break;
            }
        }

        for (int i = 0; i < numBalls; ++i) {
            Move(balls[i], angleX, angleY);
        }

        std::sort(balls.begin(), balls.end(), zSort);

        window.clear(sf::Color::White);
        for (int i = 0; i < numBalls; ++i) {
            balls[i].Draw(window);
        }

        window.draw(infoText);
        window.display();
    }

}
