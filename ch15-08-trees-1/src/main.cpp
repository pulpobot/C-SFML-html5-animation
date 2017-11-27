#include <iostream>
#include <random>
#include <algorithm>
#include "SFML\Graphics.hpp"
#include "tree.h"

float fl = 250,
        floorBounds = 200,
        vpX = 0,
        vpY = 0,
        vz = 0,
        friction = 0.98f;

bool zSort(const Tree &ballA, const Tree &ballB) {
    return ballB.zPos < ballA.zPos;
}

void Move(Tree &tree) {
    tree.zPos += vz;
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

    sf::RenderWindow window(sf::VideoMode(400, 400), "Trees 1", sf::Style::Titlebar | sf::Style::Close,
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
    infoText.setString("Press up and down arrow keys to move through scene.");

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
                    if (event.key.code == 73) //up
                        vz -= 1;
                    else if (event.key.code == 74) //down
                        vz += 1;
                    break;
            }
        }

        vz *= friction;
        window.clear(sf::Color::Black);
        for (int i = 0; i < trees.size(); ++i) {
            Move(trees[i]);
        }
        std::sort(trees.begin(), trees.end(), zSort);

        for (int i = 0; i < trees.size(); ++i) {
            trees[i].Draw(window);
        }

        window.draw(infoText);

        window.display();
    }

}
