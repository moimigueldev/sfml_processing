#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.hpp"
#include "Grid.hpp"
#include "utility.hpp"

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

  void run() {
    if (openSet.size()) {
      int winner = 0;
      for (int i = 0; i < openSet.size(); i++) {
        if (openSet[winner]->f < openSet[i]->f) {
          winner = i;
        }

        Cell* current = openSet[winner];

        openSet.erase(openSet.begin() + winner);
        closedSet.push_back(current);
      }

    } else {
      Utility::message("Done");
    }
  }

  void drawOpenSet(sf::RenderWindow& window) {
    for (int i = 0; i < openSet.size(); i++) {
      openSet[i]->draw(window, sf::Color::Green);
    }
  }

  void drawClosedSet(sf::RenderWindow& window) {
    for (int i = 0; i < closedSet.size(); i++) {
      closedSet[i]->draw(window, sf::Color::Red);
    }
  }
};

