#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.hpp"
#include "MazeGenerator.hpp"

class Game {
 private:
 public:
  std::vector<std::vector<Cell> > grid;
  int w = 50;
  int cols;
  int rows;
  Game(sf::Vector2f& windowSize) {
    cols = windowSize.x / w;
    rows = windowSize.y / w;
    setupGrid();

    // MazeGenerator::createMaze(grid);
  }

  void setupGrid() {
    grid.resize(cols);
    for (int i = 0; i < cols; i++) {
      grid[i].resize(rows);
    }

    for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
        grid[i][j] = Cell(i, j, sf::Vector2f(cols, rows), w);
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
