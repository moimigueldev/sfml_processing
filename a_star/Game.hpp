#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.hpp"
#include "Grid.hpp"

class Game {
 private:
  std::vector<std::unique_ptr<Cell> > openSet;
  std::vector<std::unique_ptr<Cell> > closedSet;
  Cell* start;
  Cell* end;
  Grid& grid;

 public:
  Game(Grid& grid_set) : grid(grid_set) {
    start = &grid.getCell(0, 0);
    end = &grid.getCell(grid.COLS - 1, grid.ROWS - 1);

    start->setAsStartingCell();
    end->setAsEndingCell();
  }

  void draw(sf::RenderWindow& window) {}
};

