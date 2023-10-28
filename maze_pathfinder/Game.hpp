#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.hpp"
#include "MazeGenerator.hpp"
#include "PathFinder.hpp"

class Game {
 private:
 public:
  std::vector<std::vector<Cell> > grid;
  int w = 100;
  int cols;
  int rows;
  MazeGenerator maze;
  PathFinder path;
  Game(sf::Vector2f& windowSize) {
    cols = windowSize.x / w;
    rows = windowSize.y / w;

    setupGrid();

    MazeGenerator maze = MazeGenerator();

    maze.createMaze(grid, cols, rows);

    path = PathFinder(grid, cols, rows);
  }

  void setupGrid() {
    grid.resize(cols);
    for (int i = 0; i < cols; i++) {
      grid[i].resize(rows);
    }

    for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
        grid[i][j] = Cell(i, j, w);
      }
    }
  }

  void draw(sf::RenderWindow& window) {
    renderGrid(window);

    path.draw(window);
  }

  void renderGrid(sf::RenderWindow& window) {
    for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
        grid[i][j].draw(window);
      }
    }
  }
};
