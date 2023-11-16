#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Cell.hpp"
#include "Grid.hpp"
#include "utility.hpp"

// float heuristic(const sf::Vector2f& a, const sf::Vector2f& b) {
//   float dx = b.x - a.x;
//   float dy = b.y - a.y;
//   return std::sqrt(dx * dx + dy * dy);
// }

float heuristic(const sf::Vector2f& a, const sf::Vector2f& b) {
  float dx = std::abs(b.x - a.x);
  float dy = std::abs(b.y - a.y);
  return std::max(dx, dy);
}

class Game {
 private:
  std::vector<Cell*> openSet;
  std::vector<Cell*> closedSet;
  std::vector<Cell*> path;
  Cell* start;
  Cell* end;
  Grid& grid;
  Cell* current;

 public:
  bool gameEnd = false;
  bool startGame = false;
  Game(Grid& grid_set) : grid(grid_set) {
    start = &grid.getCell(0, 0);
    end = &grid.getCell(grid.COLS - 1, grid.ROWS - 1);

    start->setAsStartingCell();
    end->setAsEndingCell();
    openSet.push_back(start);
  }

  void run() {
    if (startGame) {
      if (!gameEnd) {
        if (openSet.size()) {
          int winner = 0;

          for (int i = 0; i < openSet.size(); i++) {
            if (openSet[i]->f < openSet[winner]->f) {
              winner = i;
            }
          }

          current = openSet[winner];

          if (current == end) {
            Utility::message("Done: Reached The end");
            gameEnd = true;
            return;
          }

          openSet.erase(openSet.begin() + winner);
          closedSet.push_back(current);

          for (int i = 0; i < current->neighbors.size(); i++) {
            Cell* neighbor = current->neighbors[i];

            // check if closedSet does not include neighbor
            if (!neighbor->wall && std::find(closedSet.begin(), closedSet.end(),
                                             neighbor) == closedSet.end()) {
              int tempGVal;
              if (std::abs(current->i - neighbor->i) +
                      std::abs(current->j - neighbor->j) ==
                  2) {
                tempGVal = sqrt(2);
              } else {
                tempGVal = 1;
              }

              int tempG = neighbor->g + tempGVal;
              bool newPath = false;

              // check if openSet does contain neighbor
              if (std::find(openSet.begin(), openSet.end(), neighbor) !=
                  openSet.end()) {
                if (tempG < neighbor->g) {
                  neighbor->g = tempG;
                  newPath = true;
                }
              } else {
                neighbor->g = tempG;
                openSet.push_back(neighbor);
                newPath = true;
              }

              if (newPath) {
                sf::Vector2f pointA(neighbor->i, neighbor->j);
                sf::Vector2f pointB(end->i, end->j);
                neighbor->h = heuristic(pointA, pointB);
                neighbor->f = neighbor->h + neighbor->g;
                neighbor->setPrevious(current);
              }
            }
          }

        } else {
          Utility::message("Done");
          gameEnd = true;
        }
      }
    }
  }

  void drawOpenSet(sf::RenderWindow& window) {
    if (gameEnd) return;
    for (int i = 0; i < openSet.size(); i++) {
      openSet[i]->draw(window, sf::Color(6, 214, 160, 50));
    }
  }

  void drawClosedSet(sf::RenderWindow& window) {
    if (gameEnd) return;
    for (int i = 0; i < closedSet.size(); i++) {
      closedSet[i]->draw(window, sf::Color(239, 71, 111));
    }
  }

  void resetColors(sf::RenderWindow& window) {
    for (int i = 0; i < grid.COLS; ++i) {
      for (int j = 0; j < grid.ROWS; ++j) {
        Cell& cell = grid.getCell(i, j);
        if (!cell.startingCell && !cell.endingCell && !cell.wall) {
          cell.draw(
              window,
              sf::Color(
                  68, 70,
                  83));  // This will reset to the default transparent color
        }
      }
    }

    // Reset colors for the closedSet
    for (Cell* cell : closedSet) {
      cell->draw(
          window,
          sf::Color(68, 70, 83));  // Reset to the default transparent color
    }
  }

  void drawPath(sf::RenderWindow& window) {
    if (gameEnd) {
      resetColors(window);
      path.clear();
      Cell* temp = current;
      path.push_back(temp);
      while (temp->previous != nullptr) {
        path.push_back(temp->previous);
        temp = temp->previous;
      }

      for (int i = 0; i < path.size(); i++) {
        path[i]->draw(window, sf::Color(255, 209, 102));
      }
    }
  }
};

