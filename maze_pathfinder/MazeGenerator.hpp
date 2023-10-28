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

  void createMaze(std::vector<std::vector<Cell> >& grid, int cols, int rows) {
    current = &grid[0][0];
    current->visited = true;

    while (!mazeComplete) {
      Cell* next = current->checkNeighbors(grid, cols, rows);

      if (next != nullptr) {
        next->visited = true;

        current->removeWalls(*next);

        // current->highlight = false;
        stack.push_back(current);
        current = next;
      } else if (!stack.empty()) {
        current = stack.back();
        stack.pop_back();
      } else {
        Utility::message("Done");
        mazeComplete = true;
      }
    }
  }

  void draw(sf::RenderWindow& window) {}
};

