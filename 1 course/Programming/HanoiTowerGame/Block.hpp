#pragma once
#include <SFML/Graphics.hpp>

extern bool win;
extern bool lose;

class Block
{
public:
    int width;
    sf::Color color;
    int tower;
    int lvl;
    bool last = false;
    bool isMove = false;
    sf::RectangleShape* rec;

    Block(int, sf::Color, int);
    bool isMouse(sf::RenderWindow&);

    void draw(sf::RenderWindow &);
};
