#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.hpp"
#include "utility.hpp"

class PathFinder {
 private:
  Cell* startingCell = nullptr;
  Cell* endingCell = nullptr;
  Cell* current = nullptr;
  std::vector<Cell*> openSet;
  std::vector<Cell*> closedSet;
  std::vector<Cell*> path;
  bool gameEnd = false;

 public:
  PathFinder() = default;
  PathFinder(std::vector<std::vector<Cell> >& grid, int& cols, int& rows) {
    startingCell = &grid[0][0];
    endingCell = &grid[cols - 1][rows - 1];
    // startingCell->highlight = true;
    // endingCell->highlight = true;
    openSet.push_back(startingCell);
  }

  void draw(sf::RenderWindow& window) {
    if (gameEnd) {
      if (!openSet.empty()) {
        int winner = 0;

        for (int i = 0; i < openSet.size(); i++) {
          if (openSet[i]->f < openSet[winner]->f) {
            winner = i;
          }
        }

        current = openSet[winner];

        if (current == endingCell) {
          Utility::message("Done: Reached The end");
          gameEnd = true;
          return;
        }

        openSet.erase(openSet.begin() + winner);
        closedSet.push_back(current);

      } else {
        Utility::message("Done");
        gameEnd = true;
      }
    }
  }
};

