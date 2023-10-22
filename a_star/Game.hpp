#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Cell.hpp"
#include "Grid.hpp"
#include "utility.hpp"

float heuristic(const sf::Vector2f& a, const sf::Vector2f& b) {
  float dx = b.x - a.x;
  float dy = b.y - a.y;
  return std::sqrt(dx * dx + dy * dy);
}

class Game {
 private:
  std::vector<Cell*> openSet;
  std::vector<Cell*> closedSet;
  std::vector<Cell*> path;
  Cell* start;
  Cell* end;
  Grid& grid;
  bool gameEnd = false;
  Cell* current;

 public:
  Game(Grid& grid_set) : grid(grid_set) {
    start = &grid.getCell(0, 0);
    end = &grid.getCell(grid.COLS - 1, grid.ROWS - 1);

    start->setAsStartingCell();
    end->setAsEndingCell();
    openSet.push_back(start);
  }

  void run() {
    if (!gameEnd) {
      if (openSet.size()) {
        int winner = 0;

        for (int i = 0; i < openSet.size(); i++) {
          if (openSet[winner]->f < openSet[i]->f) {
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
            int tempG = neighbor->g + 1;
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
        // Utility::message("Done");
      }
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

  void drawPath(sf::RenderWindow& window) {
    //     path = [];
    // let temp = current;
    // path.push(temp);
    // while (temp.previous) {
    //   path.push(temp.previous);
    //   temp = temp.previous;
    // }
    //
    // for (let i = 0; i < path.length; i++) {
    //   path[i].show(color(0, 0, 255));
    // }
    path.clear();
    Cell* temp = current;
    path.push_back(temp);
    while (temp->previous != nullptr) {
      path.push_back(temp->previous);
      temp = temp->previous;
    }

    for (int i = 0; i < path.size(); i++) {
      path[i]->draw(window, sf::Color(200, 0, 150));
    }
  }
};

