#include <SFML/Graphics.hpp>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include "Block.hpp"

using namespace sf;
using namespace std;

const int gameWidth = 1920;
const int gameHeight = 1080;

int main()
{
    int sizeOfTower = 8;
    int turnCounter = pow(2,sizeOfTower) - 1;
    int oldpos;

    bool restart = false;

    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Hanoi");
    window.setVerticalSyncEnabled(true);

    vector<Block*> rect[3];
    sf::RectangleShape desk[3];
    sf::Color colors[8];
    colors[0] = sf::Color::Red;
    colors[1] = sf::Color(255, 128, 0);
    colors[2] = sf::Color::Yellow;
    colors[3] = sf::Color::Green;
    colors[4] = sf::Color(0, 191, 255);
    colors[5] = sf::Color::Blue;
    colors[6] = sf::Color(90, 0, 157);
    colors[7] = sf::Color::Magenta;

    Block* moving = 0;

    for(int i = 0;i < 3;i++)
    {
        desk[i].setSize(Vector2f(450, 5));
        desk[i].rotate(270);
        desk[i].setFillColor(Color(150, 75, 0));
        desk[i].setPosition(518+480*i, gameHeight/2);
    }

    for(int i = 0;i < sizeOfTower;i++)
    {
        rect[0].push_back(new Block(300-38*i,colors[i],i));
    }
    rect[0][7]->last = true;

    Font font;
    font.loadFromFile("Kavivanar-Regular.ttf");

    Text turns;
    turns.setFont(font);
    turns.setCharacterSize(30);
    turns.setPosition(gameWidth-300, gameHeight/2 + 100);
    turns.setColor(Color::Black);

    Text Win;
    Win.setString("You Win!!!");
    Win.setFont(font);
    Win.setCharacterSize(200);
    Win.setPosition(gameWidth/3, 550);
    Win.setColor(Color::Red);

    Text LoseStr;
    LoseStr.setString("You Lose");
    LoseStr.setFont(font);
    LoseStr.setCharacterSize(200);
    LoseStr.setPosition(gameWidth/3, 550);
    LoseStr.setColor(Color::Red);

    Text RestartStr;
    RestartStr.setString("Press \"R\" to restart");
    RestartStr.setFont(font);
    RestartStr.setCharacterSize(30);
    RestartStr.setPosition(gameWidth/2-100, 800);
    RestartStr.setColor(Color::Black);

    Text Rules[4];
    Rules[0].setString("Rules:");
    Rules[1].setString("1)All blocks must be moved to the third tower in 255 moves");
    Rules[2].setString("2)You can only take the top blocks");
    Rules[3].setString("3)You can not put bigger blocks on smaller ones");
    for(int i = 0;i < 4;i++)
    {
        Rules[i].setFont(font);
        Rules[i].setCharacterSize(20);
        Rules[i].setPosition(100, 680+50*i);
        Rules[i].setColor(Color::Black);
    }



    while(window.isOpen())
    {
        Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);

        sf::Event event;

        for(int i = 0;i < 3;i++)
        {
            for(int j = 0;j < rect[i].size();j++)
            {
                if(j == rect[i].size()-1)
                {
                    rect[i][j]->last = true;
                }
                else
                {
                    rect[i][j]->last = false;
                }
            }
        }



        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed ||
              (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
                if(!win && !lose){
                    if (event.type == Event::MouseButtonPressed)
                        if (event.key.code == Mouse::Left)
                        {
                            for(int i = 0;i < 3;i++){
                                for(int j = 0;j < rect[i].size();j++){
                                    if(rect[i][j]->isMouse(window) && rect[i][j]->last){
                                        rect[i][j]->isMove = true;
                                        moving = rect[i][j];
                                        oldpos = i;
                                    }
                                }

                            }
                        }
                    if(event.type == Event::MouseButtonReleased && moving!=0){
                        bool flag = 1;
                        Vector2i pos = Mouse::getPosition(window);
                        int newpos = 0;
                        if(pos.x < 720){
                            newpos = 0;
                        }else if(pos.x < 1200){
                            newpos = 1;
                        }else{
                            newpos = 2;
                        }
                        if(rect[newpos].size()>0 && rect[newpos][rect[newpos].size()-1]->width < moving->width){
                            flag = 0;
                        }
                        if(flag){
                            rect[moving->tower].pop_back();
                            rect[newpos].push_back(moving);
                            moving->tower = newpos;
                            moving->lvl = rect[newpos].size()-1;
                            moving->isMove = false;
                            moving = 0;
                            if(!(oldpos == newpos)){
                                turnCounter--;
                            }
                        }else{
                            moving->isMove = false;
                            moving = 0;
                        }
                    }
                }
                    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R){
                        restart = true;
                    }

        if(rect[2].size() == sizeOfTower)
        {
            win = true;
        }
        if(rect[2].size() != sizeOfTower && turnCounter == 0)
        {
            lose = true;
        }

        if(restart)
        {
            for(int i = 0; i < 3; i++)
            {
                rect[i].clear();
            }
            for(int i = 0;i < sizeOfTower;i++)
            {
                rect[0].push_back(new Block(300-38*i,colors[i],i));
            }
            rect[0][7]->last = true;
            turnCounter = pow(2, sizeOfTower) - 1;
            restart = false;
            win = false;
            lose = false;
        }

        window.clear(Color::White);

        for(int i = 0;i < 3;i++)
            window.draw(desk[i]);

        for(int i = 0;i < 4;i++)
            window.draw(Rules[i]);

        for(int i = 0;i < 3;i++)
        {
            for(int j = 0;j < rect[i].size();j++)
            {
                rect[i][j]->draw(window);
            }

        }

        if(win)
        {
            window.draw(Win);
            window.draw(RestartStr);
        }
        if(lose)
        {
            window.draw(LoseStr);
            window.draw(RestartStr);
        }
        ostringstream turnCounterStr;
        turnCounterStr << turnCounter;
        turns.setString("Turns: " + turnCounterStr.str());
        window.draw(turns);

        window.display();
    }
    }

    return 0;
}
