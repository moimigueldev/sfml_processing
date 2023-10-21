#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Cell {
 private:
  int i;
  int j;
  sf::RectangleShape shape;
  sf::CircleShape center;

 public:
  Cell() = default;
  Cell(float i_pos, float j_pos, sf::Vector2f dims) {
    i = i_pos;
    j = j_pos;

    shape.setPosition(i * dims.x, j * dims.y);
    shape.setSize(dims);
    // shape.setSize(sf::Vector2f(dims.x - 1, dims.y - 1));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::White);

    center.setRadius(5);
    center.setOrigin(5, 5);
    center.setFillColor(sf::Color::Red);
    center.setPosition(shape.getPosition().x, shape.getPosition().y);
  }

  void draw(sf::RenderWindow& window) {
    window.draw(shape);
    // window.draw(center);
  }
};

