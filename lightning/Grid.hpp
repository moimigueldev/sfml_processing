#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.hpp"
#include "WindowUtility.hpp"
#include "utility.hpp"

class Grid {
 private:
  std::vector<std::vector<Cell> > grid;

 public:
  int size = 20;
  int cols = WindowUtility::windowSize.x / size;
  int rows = WindowUtility::windowSize.y / size;
  Grid() {
    grid.resize(cols);
    for (int i = 0; i < cols; i++) {
      grid[i].resize(rows);
    }

    for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
        grid[i][j] = Cell(sf::Vector2f(i, j), size);
      }
    }
  }

  void draw(sf::RenderWindow& window) {
    for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
        grid[i][j].draw(window);
      }
    }
  }
};
