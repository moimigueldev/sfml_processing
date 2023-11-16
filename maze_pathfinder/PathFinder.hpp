#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.hpp"
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

class PathFinder {
 private:
  Cell* startingCell = nullptr;
  Cell* endingCell = nullptr;
  Cell* current = nullptr;
  std::vector<Cell*> openSet;
  std::vector<Cell*> closedSet;
  std::vector<Cell*> path;

 public:
  bool gameEnd = false;
  PathFinder() = default;
  PathFinder(std::vector<std::vector<Cell> >& grid, int& cols, int& rows) {
    startingCell = &grid[0][0];
    // endingCell = &grid[cols - 1][rows - 1];
    endingCell = &grid[cols / 2][rows / 2];
    // startingCell->highlight = true;
    endingCell->highlight = true;
    openSet.push_back(startingCell);
  }

  void draw(sf::RenderWindow& window) {
    if (!gameEnd) {
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

        for (int i = 0; i < current->neighborCells.size(); i++) {
          Cell* neighbor = current->neighborCells[i];

          if (std::find(closedSet.begin(), closedSet.end(), neighbor) ==
              closedSet.end()) {
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
              sf::Vector2f pointB(endingCell->i, endingCell->j);
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

  void drawOpenSet(sf::RenderWindow& window) {
    for (int i = 0; i < openSet.size(); i++) {
      openSet[i]->drawListSets(window, sf::Color::Blue);
    }
  }

  void drawClosedSet(sf::RenderWindow& window) {
    for (int i = 0; i < closedSet.size(); i++) {
      closedSet[i]->drawListSets(window, sf::Color(239, 71, 111));
    }
  }

  void drawPath(sf::RenderWindow& window) {
    if (gameEnd) {
      path.clear();
      Cell* temp = current;
      path.push_back(temp);
      while (temp->previous != nullptr) {
        path.push_back(temp->previous);
        temp = temp->previous;
      }

      for (int i = 0; i < path.size(); i++) {
        path[i]->drawPath(window, sf::Color(106, 96, 242));
      }
    }
  }
};

