#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "utility.hpp"

class Cell {
 private:
  // sf::Color wallColor = sf::Color(183, 183, 183);
  sf::Color wallColor = sf::Color(244, 211, 94);
  sf::RectangleShape highlightShape;
  sf::RectangleShape visitedShape;
  sf::RectangleShape wallShape;
  sf::RectangleShape listSets;
  sf::RectangleShape pathShape;

 public:
  int i;
  int j;
  sf::Vector2f position;
  int w;
  Cell() = default;
  sf::VertexArray topLine = sf::VertexArray(sf::Lines, 2);
  sf::VertexArray rightLine = sf::VertexArray(sf::Lines, 2);
  sf::VertexArray bottomLine = sf::VertexArray(sf::Lines, 2);
  sf::VertexArray leftLine = sf::VertexArray(sf::Lines, 2);
  bool visited = false;
  bool highlight = false;
  Cell *previous = nullptr;
  int g = 0;
  int h = 0;
  int f = 0;
  bool startingCell = false;
  bool endingCell = false;
  std::vector<Cell *> neighborCells;
  bool wall = false;

  // top, right, bottom, left
  std::array<bool, 4> walls = {true, true, true, true};

  Cell(int i_pos, int j_pos, int &width) {
    i = i_pos;
    j = j_pos;
    w = width;

    position = sf::Vector2f(i * w, j * w);

    setupShapes();

    setupWalls();
  }

  Cell *checkNeighbors(std::vector<std::vector<Cell> > &grid, int &cols,
                       int &rows) {
    std::vector<Cell *> neighbors;

    if (i > 0) {  // check above
      Cell *top = &grid[i - 1][j];
      if (!top->visited) {
        neighbors.push_back(top);
      }
    }

    if (j + 1 < rows) {  // check right
      Cell *right = &grid[i][j + 1];
      if (!right->visited) {
        neighbors.push_back(right);
      }
    }

    if (i + 1 < cols) {  // check below
      Cell *bottom = &grid[i + 1][j];
      if (!bottom->visited) {
        neighbors.push_back(bottom);
      }
    }

    if (j > 0) {  // check left
      Cell *left = &grid[i][j - 1];
      if (!left->visited) {
        neighbors.push_back(left);
      }
    }

    if (!neighbors.empty()) {
      int index = Utility::genRandomInt(0, neighbors.size() - 1);
      return neighbors[index];
    }

    return nullptr;
  }

  void setPrevious(Cell *prev) { previous = prev; }

  void removeWalls(Cell &neighbor) {
    int x = i - neighbor.i;

    if (x == 1) {
      leftLine[0].color.a = 0;
      leftLine[1].color.a = 0;
      neighbor.rightLine[0].color.a = 0;
      neighbor.rightLine[1].color.a = 0;
      walls[3] = false;           // update left wall for current cell
      neighbor.walls[1] = false;  // update right wall for neighbor
    } else if (x == -1) {
      rightLine[0].color.a = 0;
      rightLine[1].color.a = 0;
      neighbor.leftLine[0].color.a = 0;
      neighbor.leftLine[1].color.a = 0;
      walls[1] = false;           // update right wall for current cell
      neighbor.walls[3] = false;  // update left wall for neighbor
    }

    int y = j - neighbor.j;

    if (y == 1) {
      topLine[0].color.a = 0;
      topLine[1].color.a = 0;
      neighbor.bottomLine[0].color.a = 0;
      neighbor.bottomLine[1].color.a = 0;
      walls[0] = false;           // update top wall for current cell
      neighbor.walls[2] = false;  // update bottom wall for neighbor
    } else if (y == -1) {
      bottomLine[0].color.a = 0;
      bottomLine[1].color.a = 0;
      neighbor.topLine[0].color.a = 0;
      neighbor.topLine[1].color.a = 0;
      walls[2] = false;           // update bottom wall for current cell
      neighbor.walls[0] = false;  // update top wall for neighbor
    }
  }

  void draw(sf::RenderWindow &window) {
    window.draw(topLine);
    window.draw(rightLine);
    window.draw(bottomLine);
    window.draw(leftLine);

    if (highlight) {
      window.draw(highlightShape);
    }

    if (visited) {
      window.draw(visitedShape);
    }

    // todo: is a black wall necessary?
    // if (wall) {
    //   window.draw(wallShape);
    // }
  }

  void setupNeighbors(sf::Vector2i colsRows,
                      std::vector<std::vector<Cell> > &grid) {
    int cols = colsRows.x;
    int rows = colsRows.y;

    // Top
    if (j > 0) {
      Cell *topNeighbor = &grid[i][j - 1];
      if (!walls[0] && !topNeighbor->walls[2]) {
        neighborCells.push_back(topNeighbor);
      }
    }

    // Right
    if (i + 1 < cols) {
      Cell *rightNeighbor = &grid[i + 1][j];
      if (!walls[1] && !rightNeighbor->walls[3]) {
        neighborCells.push_back(rightNeighbor);
      }
    }

    // Bottom
    if (j + 1 < rows) {
      Cell *bottomNeighbor = &grid[i][j + 1];
      if (!walls[2] && !bottomNeighbor->walls[0]) {
        neighborCells.push_back(bottomNeighbor);
      }
    }

    // Left
    if (i > 0) {
      Cell *leftNeighbor = &grid[i - 1][j];
      if (!walls[3] && !leftNeighbor->walls[1]) {
        neighborCells.push_back(leftNeighbor);
      }
    }
  }

  void setupWalls() {
    // Top line
    topLine[0] = position;
    topLine[1] = sf::Vector2f(position.x + w, position.y);
    topLine[0].color = wallColor;
    topLine[1].color = wallColor;

    // Right line
    rightLine[0] = sf::Vector2f(position.x + w, position.y);
    rightLine[1] = sf::Vector2f(position.x + w, position.y + w);
    rightLine[0].color = wallColor;
    rightLine[1].color = wallColor;

    // Bottom line
    bottomLine[0] = sf::Vector2f(position.x + w, position.y + w);
    bottomLine[1] = sf::Vector2f(position.x, position.y + w);
    bottomLine[0].color = wallColor;
    bottomLine[1].color = wallColor;

    // Left line
    leftLine[0] = sf::Vector2f(position.x, position.y + w);
    leftLine[1] = position;
    leftLine[0].color = wallColor;
    leftLine[1].color = wallColor;

    float randomFloat = Utility::genRandomFloat(0, 1.0f);
    if (randomFloat < 0.35f) {
      wall = true;
    }
  }

  void setupShapes() {
    highlightShape.setPosition(position);
    highlightShape.setSize(sf::Vector2f(w, w));
    highlightShape.setFillColor(sf::Color(242, 100, 25));

    visitedShape.setPosition(position);
    visitedShape.setSize(sf::Vector2f(w, w));
    visitedShape.setFillColor(sf::Color(255, 0, 255, 0));

    wallShape.setPosition(position);
    wallShape.setSize(sf::Vector2f(w, w));
    wallShape.setFillColor(sf::Color(0, 0, 0));

    listSets.setPosition(position);
    listSets.setSize(sf::Vector2f(w, w));
    listSets.setFillColor(sf::Color(0, 0, 0));

    pathShape.setPosition(position);
    pathShape.setSize(sf::Vector2f(w, w));
    pathShape.setFillColor(sf::Color(0, 0, 255, 10));
  }

  void drawListSets(sf::RenderWindow &window, sf::Color color) {
    listSets.setFillColor(color);
    window.draw(listSets);
  }

  void drawPath(sf::RenderWindow &window, sf::Color color) {
    pathShape.setFillColor(color);
    window.draw(pathShape);
  }
};
