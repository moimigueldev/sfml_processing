#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.hpp"

class Grid {
 private:
  const int COLS = 25;
  const int ROWS = 25;
  float w;
  float h;
  std::vector<std::vector<Cell> > grid;
  sf::Vector2f windowDims;

 public:
  Grid(sf::Vector2f windowSize) {
    windowDims = windowSize;
    w = windowDims.x / COLS;
    h = windowDims.y / ROWS;

    setupGrid(windowSize);
  }

  void setupGrid(sf::Vector2f& windowSize) {
    grid.resize(COLS);
    for (int i = 0; i < COLS; ++i) {
      grid[i].resize(ROWS);
    }

    for (int i = 0; i < COLS; i++) {
      for (int j = 0; j < ROWS; j++) {
        grid[i][j] = Cell(i, j, sf::Vector2f(w, h));
      }
    }
  }

  void draw(sf::RenderWindow& window) {
    for (int i = 0; i < COLS; i++) {
      for (int j = 0; j < ROWS; j++) {
        grid[i][j].draw(window);
      }
    }
  }
};

