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
  const int COLS = 30;
  const int ROWS = 30;

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

  void setWall(sf::Vector2i mousePos) {
    int mouseX = mousePos.x;
    int mouseY = mousePos.y;
    bool cellFound = false;
    for (int i = 0; i < COLS; i++) {
      if (cellFound) break;
      for (int j = 0; j < ROWS; j++) {
        Cell& cell = grid[i][j];
        sf::Vector2i cellPos(cell.i * w, cell.j * h);
        sf::Vector2i center(cellPos.x + w / 2, cellPos.y + h / 2);
        if (mouseX > center.x - w / 2 && mouseX < center.x + w / 2 &&
            mouseY > center.y - h / 2 && mouseY < center.y + h / 2) {
          cell.setWall();
          cellFound = true;
          break;
        }
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

