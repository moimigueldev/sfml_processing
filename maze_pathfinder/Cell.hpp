#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "utility.hpp"

class Cell {
 private:
  sf::Color wallColor = sf::Color(183, 183, 183);
  sf::RectangleShape highlightShape;
  sf::RectangleShape visitedShape;

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

    if (j + 1 < cols) {  // check right
      Cell *right = &grid[i][j + 1];
      if (!right->visited) {
        neighbors.push_back(right);
      }
    }

    if (i + 1 < rows) {  // check below
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

  void removeWalls(Cell &neighbor) {
    int x = i - neighbor.i;

    if (x == 1) {
      leftLine[0].color.a = 0;
      leftLine[1].color.a = 0;
      neighbor.rightLine[0].color.a = 0;
      neighbor.rightLine[1].color.a = 0;
    } else if (x == -1) {
      rightLine[0].color.a = 0;
      rightLine[1].color.a = 0;
      neighbor.leftLine[0].color.a = 0;
      neighbor.leftLine[1].color.a = 0;
    }

    int y = j - neighbor.j;

    if (y == 1) {
      topLine[0].color.a = 0;
      topLine[1].color.a = 0;
      neighbor.bottomLine[0].color.a = 0;
      neighbor.bottomLine[1].color.a = 0;
    } else if (y == -1) {
      bottomLine[0].color.a = 0;
      bottomLine[1].color.a = 0;
      neighbor.topLine[0].color.a = 0;
      neighbor.topLine[1].color.a = 0;
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
  }

  void setupShapes() {
    highlightShape.setPosition(position);
    highlightShape.setSize(sf::Vector2f(w, w));
    highlightShape.setFillColor(sf::Color::Green);

    visitedShape.setPosition(position);
    visitedShape.setSize(sf::Vector2f(w, w));
    visitedShape.setFillColor(sf::Color(255, 0, 255, 0));
  }
};
