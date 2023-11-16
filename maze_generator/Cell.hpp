#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

struct Wall {
  int Top = 0;
  int Right = 1;
  int Bottom = 2;
  int Left = 3;
};

class Cell {
 private:
  sf::RectangleShape cell;
  sf::CircleShape point;

  int width = 40;  // cell will be a square
  int outlineThickness = 0;
  Wall cellWalls;
  // Top Right Bottom Left
  int cols;
  int rows;

 public:
  std::array<bool, 4> walls = {true, true, true, true};
  int i;  // cols
  int j;  // rows
  bool isVisited = false;
  Cell(int x, int y, int col, int row) {
    i = x;
    j = y;
    cols = col;
    rows = row;
    cell.setPosition(i * width, j * width);
    cell.setSize(sf::Vector2f(width, width));
    cell.setOutlineThickness(outlineThickness);
    cell.setOutlineColor(sf::Color::Transparent);
    cell.setOrigin(0, 0);
    cell.setFillColor(sf::Color::Green);

    point.setRadius(5);
    point.setOrigin(5, 5);
    point.setFillColor(sf::Color::Red);
    point.setPosition(i * width, j * width);
  }

  Cell* checkNeighbors(const std::vector<std::unique_ptr<Cell> >& grid) {
    std::vector<Cell*> neighbors;

    int idx;

    idx = index(i, j - 1);
    if (idx != -1) {
      Cell* top = grid[idx].get();
      if (!top->isVisited) {
        neighbors.push_back(top);
      }
    }

    idx = index(i + 1, j);
    if (idx != -1) {
      Cell* right = grid[idx].get();
      if (!right->isVisited) {
        neighbors.push_back(right);
      }
    }

    idx = index(i, j + 1);
    if (idx != -1) {
      Cell* bottom = grid[idx].get();
      if (!bottom->isVisited) {
        neighbors.push_back(bottom);
      }
    }

    idx = index(i - 1, j);
    if (idx != -1) {
      Cell* left = grid[idx].get();
      if (!left->isVisited) {
        neighbors.push_back(left);
      }
    }

    // Return a random neighbor or nullptr if no neighbors are available
    if (neighbors.size() > 0) {
      int randomIdx = rand() % neighbors.size();
      return neighbors[randomIdx];
    } else {
      return nullptr;
    }
  }

  void draw(sf::RenderWindow& window) {
    int x = i * width;
    int y = j * width;
    if (isVisited) {
      cell.setFillColor(sf::Color(60, 82, 51, 100));  // 128 is 50% of 255
      window.draw(cell);
    }

    if (walls[cellWalls.Top]) {
      sf::VertexArray topLine(sf::Lines, 2);
      topLine[0] = sf::Vector2f(x, y);
      topLine[1] = sf::Vector2f(x + width, y);
      topLine[0].color = sf::Color(244, 211, 94);
      topLine[1].color = sf::Color(244, 211, 94);
      window.draw(topLine);
    }

    if (walls[cellWalls.Right]) {
      sf::VertexArray rightLine(sf::Lines, 2);
      rightLine[0] = sf::Vector2f(x + width, y);
      rightLine[1] = sf::Vector2f(x + width, y + width);
      rightLine[0].color = sf::Color(244, 211, 94);
      rightLine[1].color = sf::Color(244, 211, 94);
      window.draw(rightLine);
    }

    if (walls[cellWalls.Bottom]) {
      sf::VertexArray bottomLine(sf::Lines, 2);
      bottomLine[0] = sf::Vector2f(x + width, y + width);
      bottomLine[1] = sf::Vector2f(x, y + width);
      bottomLine[0].color = sf::Color(244, 211, 94);
      bottomLine[1].color = sf::Color(244, 211, 94);

      window.draw(bottomLine);
    }

    if (walls[cellWalls.Left]) {
      sf::VertexArray leftLine(sf::Lines, 2);
      leftLine[0] = sf::Vector2f(x, y + width);
      leftLine[1] = sf::Vector2f(x, y);
      leftLine[0].color = sf::Color(244, 211, 94);
      leftLine[1].color = sf::Color(244, 211, 94);

      window.draw(leftLine);
    }
  }

  void highlight(sf::RenderWindow& window) {
    cell.setFillColor(sf::Color::Red);
    window.draw(cell);
  }

  int index(int x, int y) {
    if (x < 0 || y < 0 || x > cols - 1 || y > rows - 1) {
      return -1;
    }

    return x + y * cols;
  }
};

