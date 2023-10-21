#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.hpp"
#include "Grid.hpp"

class Game {
 private:
  std::vector<Cell*> openSet;
  std::vector<Cell*> closedSet;
  Cell* start;
  Cell* end;
  Grid& grid;

 public:
  Game(Grid& grid_set) : grid(grid_set) {
    start = &grid.getCell(0, 0);
    end = &grid.getCell(grid.COLS - 1, grid.ROWS - 1);

    start->setAsStartingCell();
    end->setAsEndingCell();
    openSet.push_back(start);
  }

  void draw(sf::RenderWindow& window) {
    // for (int i = 0; i < openSet.size(); i++) {
    //   openSet[i]->draw()
    //
    // }
  }
};

