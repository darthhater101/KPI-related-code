#include "Block.hpp"

using namespace sf;

bool win = false;
bool lose = false;

Block::Block(int wid, sf::Color col, int pos)
{
    rec = new RectangleShape;
    width = wid;
    color = col;
    lvl = pos;
    rec->setSize(Vector2f(width,50));
    rec->setFillColor(col);
    tower =0;
    rec->setOutlineColor(Color::Black);
}

void Block::draw(sf::RenderWindow &window)
{
    if(!isMove)
    {
        rec->setPosition(520+(480*tower)-width/2,(1080/2)-50-lvl*50);
    }
    else
    {
        Vector2i pos = Mouse::getPosition(window);
        rec->setPosition(pos.x-width-2,pos.y-25);
    }
    if((this->isMouse(window) || isMove) && this->last && (!win || !lose))
    {
        rec->setOutlineThickness(2);
    }
    else
    {
        rec->setOutlineThickness(0);
    }
    window.draw(*rec);
}

bool Block::isMouse(RenderWindow& window){
    Vector2f size = rec->getSize();
    Vector2f pos = rec->getPosition();


    if(IntRect(pos.x,pos.y,size.x,size.y).contains(Mouse::getPosition(window)))
    {
        return true;
    }
    return false;
}
