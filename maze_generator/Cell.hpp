#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include <array>


struct Wall {
  int Top = 0;
  int Right = 1;
  int Bottom = 2;
  int Left = 3;
};

class Cell {
  private:
    sf::RectangleShape cell;
    sf::CircleShape point;
    int i; // cols
    int j; // rows
    int width = 50; // cell will be a square
    int outlineThickness = 1;
    bool isVisited = false;
    Wall cellWalls;
    // Top Right Bottom Left
    std::array<bool, 4> walls = {true, true, true, true};
    
  public:
   Cell(int x, int y) {
     i = x;
     j = y;
     cell.setPosition(i * width, j * width);
     cell.setSize(sf::Vector2f(width, width));
     cell.setFillColor(sf::Color::Transparent);
     cell.setOutlineThickness(outlineThickness);
     cell.setOutlineColor(sf::Color::White);
     cell.setOrigin(0, 0);


     point.setRadius(5);
     point.setOrigin(5, 5);
     point.setFillColor(sf::Color::Red);
     point.setPosition(i * width, j * width);

   }


   void draw(sf::RenderWindow& window) {


     int x = i * width;
     int y = j * width;
    

     if(walls[cellWalls.Top]) {
       sf::VertexArray topLine(sf::Lines, 2);
       topLine[0] = sf::Vector2f(x, y);
       topLine[1] = sf::Vector2f(x + width, y);
       window.draw(topLine);
     }

     if(walls[cellWalls.Right]) {
       sf::VertexArray rightLine(sf::Lines, 2);
       rightLine[0] = sf::Vector2f(x+ width, y);
       rightLine[1] = sf::Vector2f(x + width, y + width);
       window.draw(rightLine);

     }

     if(walls[cellWalls.Bottom]) {
       sf::VertexArray bottomLine(sf::Lines, 2);
       bottomLine[0] = sf::Vector2f(x + width, y + width );
       bottomLine[1] = sf::Vector2f(x , y + width);
       window.draw(bottomLine);
     }

     if(walls[cellWalls.Left]) {
       sf::VertexArray leftLine(sf::Lines, 2);
       leftLine[0] = sf::Vector2f(x, y + width);
       leftLine[1] = sf::Vector2f(x , y);
       window.draw(leftLine);
     }
   }





};

