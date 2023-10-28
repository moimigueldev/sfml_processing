#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.hpp"
#include "utility.hpp"

class MazeGenerator {
 private:
  bool mazeComplete = false;
  std::vector<Cell*> stack;
  Cell* current = nullptr;
  Cell* next = nullptr;

 public:
  MazeGenerator() {}

  void createMaze(std::vector<std::vector<Cell> >& grid) {
    current = &grid[0][0];
    current->highlight = true;
    std::vector<Cell*> neighbors = current->checkNeighbors(grid);
    // int rows, cols = grid.size();
    while (!mazeComplete) {
      Utility::message("Hello");

      mazeComplete = true;
    }
  }

  void draw(sf::RenderWindow& window) {}
};

