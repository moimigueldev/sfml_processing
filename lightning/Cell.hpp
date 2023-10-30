#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "WindowUtility.hpp"
#include "utility.hpp"

class Cell {
 private:
  sf::RectangleShape shape;
  sf::Vector2f windowSize = WindowUtility::windowSize;
  sf::Vector2f pos;
  int w;

 public:
  Cell() = default;
  Cell(sf::Vector2f position, int size) {
    w = size;
    pos = position;

    setupShape();
  }

  void draw(sf::RenderWindow& window) { window.draw(shape); }

  void setupShape() {
    shape.setPosition(pos.x * w, pos.y * w);
    shape.setSize(sf::Vector2f(w, w));
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color(255, 255, 255, 25));
    shape.setFillColor(sf::Color::Transparent);
  }
};
