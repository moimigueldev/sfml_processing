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
  int w = 30;
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

    for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
        grid[i][j].setupNeighbors(sf::Vector2i(cols, rows), grid);
      }
    }

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
    path.draw(window);
    if (!path.gameEnd) {
      path.drawOpenSet(window);
      path.drawClosedSet(window);
    }
    path.drawPath(window);

    renderGrid(window);
  }

  void renderGrid(sf::RenderWindow& window) {
    for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
        grid[i][j].draw(window);
      }
    }
  }
};
