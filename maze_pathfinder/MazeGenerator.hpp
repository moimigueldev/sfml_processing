#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.hpp"
#include "utility.hpp"

class MazeGenerator {
 private:
 public:
  MazeGenerator() {}

  static void createMaze(std::vector<std::vector<Cell> >& grid) {
    int rows, cols = grid.size();
    Utility::message(rows);
    Utility::message(cols);
  }

  void draw(sf::RenderWindow& window) {}
};

