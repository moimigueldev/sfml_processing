#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.hpp"
#include "Grid.hpp"
#include "utility.hpp"

class Game {
 private:
  sf::RectangleShape shape;

 public:
  Grid grid;
  sf::Vector2f size = sf::Vector2f(1.0f, grid.size);
  Game() {
    shape.setPosition(grid.cols / 2.0f * grid.size, 0.0f);
    shape.setSize(size);
    shape.setOutlineThickness(3);
    shape.setOutlineColor(sf::Color::White);
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(size.x / 2, size.y / 2);
    shape.setRotation(45.f);
  }

  void draw(sf::RenderWindow& window) {
    grid.draw(window);
    window.draw(shape);
  }
};
