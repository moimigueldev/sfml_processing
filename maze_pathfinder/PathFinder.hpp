#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.hpp"
#include "utility.hpp"

class PathFinder {
 private:
  Cell* startingCell = nullptr;
  Cell* endingCell = nullptr;
  std::vector<Cell*> openSet;
  std::vector<Cell*> closedSet;
  std::vector<Cell*> path;

 public:
  PathFinder() = default;
  PathFinder(std::vector<std::vector<Cell> >& grid, int& cols, int& rows) {
    startingCell = &grid[0][0];
    endingCell = &grid[cols - 1][rows - 1];
    startingCell->highlight = true;
    endingCell->highlight = true;
  }

  void draw(sf::RenderWindow& window) {}
};

