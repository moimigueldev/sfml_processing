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
    // if (next) {
    //   next.visited = true;
    //   stack.push(current);
    //   removeWalls(current, next);
    //   current = next;
    // } else {
    //   if (stack.length) {
    //     current = stack.pop();
    //   } else {
    //     console.log("DONE");
    //     noLoop();
    //   }
    // }

    current = &grid[0][0];
    current->visited = true;

    while (!mazeComplete) {
      // Utility::message("In here");
      // current->highlight = true;
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
        Utility::message("DONe");
        mazeComplete = true;
      }
    }
  }

  void draw(sf::RenderWindow& window) {}
};

