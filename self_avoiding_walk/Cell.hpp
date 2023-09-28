#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>

class Cell {
  private:
    sf::RectangleShape cell; 
    int width; // square
    const int OUTLINE_THICKNESS = 1; // square
    const sf::Color OUTLINE_COLOR = sf::Color(252, 247, 248, 100); // square
  public:
   Cell(sf::Vector2f pos, int size) {
      width = size;
      cell.setPosition(pos.x * width, pos.y * width);
      cell.setSize(sf::Vector2f(width,   width ));
      cell.setFillColor(sf::Color::Transparent);
      cell.setOutlineThickness(OUTLINE_THICKNESS);
      cell.setOutlineColor(OUTLINE_COLOR);
      cell.setOrigin(sf::Vector2f(0, 0));
   }


   void draw(sf::RenderWindow& window) {
          window.draw(cell);
   }



};

