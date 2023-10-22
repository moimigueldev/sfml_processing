#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.hpp"

class Grid {
 private:
  float w;
  float h;
  sf::Vector2f windowDims;

 public:
  const int COLS = 5;
  const int ROWS = 5;

  std::vector<std::vector<Cell> > grid;

  Grid(sf::Vector2f windowSize) {
    windowDims = windowSize;
    w = windowDims.x / COLS;
    h = windowDims.y / ROWS;

    setupGrid(windowSize);

    for (int i = 0; i < COLS; i++) {
      for (int j = 0; j < ROWS; j++) {
        grid[i][j].setupNeighbors(sf::Vector2i(COLS, ROWS), *this);
      }
    }
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

  Cell& getCell(int col, int row) { return grid[col][row]; }

  void draw(sf::RenderWindow& window) {
    for (int i = 0; i < COLS; i++) {
      for (int j = 0; j < ROWS; j++) {
        grid[i][j].draw(window);
      }
    }
  }
};

