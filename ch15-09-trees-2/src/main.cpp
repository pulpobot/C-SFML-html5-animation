#include <iostream>
#include <random>
#include <algorithm>
#include "SFML\Graphics.hpp"
#include "tree.h"

float fl = 250,
        vpX = 0,
        vpY = 0,
        floorBounds = 50,
        ax = 0,
        ay = 0,
        az = 0,
        vx = 0,
        vy = 0,
        vz = 0,
        gravity = 0.3f,
        friction = 0.98f;

bool zSort(const Tree &treeA, const Tree &treeB) {
    return treeB.zPos < treeA.zPos;
}

void Move(Tree &tree) {
    tree.xPos += vx;
    tree.yPos += vy;
    tree.zPos += vz;
    if(tree.yPos < floorBounds)
        tree.yPos = floorBounds;
    if (tree.zPos < -fl) {
        tree.zPos += 10000;
    }
    if (tree.zPos > 10000 - fl) {
        tree.zPos -= 10000;
    }
    float scale = fl / (fl + tree.zPos);
    tree.SetScale(scale);
    tree.SetX(vpX + tree.xPos * scale);
    tree.SetY(vpY + tree.yPos * scale);
    tree.Alpha(scale);
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Trees 2", sf::Style::Titlebar | sf::Style::Close,
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
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(sf::Vector2f(5, window.getSize().y - 20));
    infoText.setString("Press arrow keys to move through scene, spacebar to fly.");

    std::mt19937 m(time(NULL));
    std::uniform_real_distribution<float> t(0.0f, 1.0f);

    std::vector<Tree> trees = std::vector<Tree>();
    int numTrees = 100;

    for (int i = 0; i < numTrees; ++i) {
        trees.emplace_back(Tree(0, 0, 0, m, t));
        trees[i].xPos = t(m) * 2000 - 1000;
        trees[i].yPos = floorBounds;
        trees[i].zPos = t(m) * 10000;
    }

    vpX = window.getSize().x / 2.0f;
    vpY = window.getSize().y / 2.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Key::Up)
                        az = -1;
                    else if (event.key.code == sf::Keyboard::Key::Down)
                        az = 1;
                    if (event.key.code == sf::Keyboard::Key::Left)
                        ax = 1;
                    else if (event.key.code == sf::Keyboard::Key::Right)
                        ax = -1;
                    if (event.key.code == sf::Keyboard::Key::Space)
                        ay = 1;
                    break;
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::Key::Up || event.key.code == sf::Keyboard::Key::Down)
                        az = 0;
                    if (event.key.code == sf::Keyboard::Key::Left || event.key.code == sf::Keyboard::Key::Right)
                        ax = 0;
                    if (event.key.code == sf::Keyboard::Key::Space)
                        ay = 0;
                    break;
            }
        }

        vx += ax;
        vy += ay;
        vz += az;
        vy -= gravity;
        window.clear(sf::Color::Black);
        for (int i = 0; i < trees.size(); ++i) {
            Move(trees[i]);
        }

        vx *= friction;
        vy *= friction;
        vz *= friction;

        std::sort(trees.begin(), trees.end(), zSort);

        for (int i = 0; i < trees.size(); ++i) {
            trees[i].Draw(window);
        }

        window.draw(infoText);

        window.display();
    }

}
