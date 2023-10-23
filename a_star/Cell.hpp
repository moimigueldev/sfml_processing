#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

// #include "Grid.hpp"
#include "utility.hpp"
class Cell {
 private:
  sf::RectangleShape shape;
  sf::CircleShape center;

 public:
  int i;
  int j;
  Cell* previous = nullptr;
  int g = 0;
  int h = 0;
  int f = 0;
  bool startingCell = false;
  bool endingCell = false;
  std::vector<Cell*> neighbors;
  bool wall = false;
  Cell() = default;
  Cell(float i_pos, float j_pos, sf::Vector2f dims) {
    i = i_pos;
    j = j_pos;

    shape.setPosition(i * dims.x, j * dims.y);
    shape.setSize(dims);
    // shape.setSize(sf::Vector2f(dims.x - 1, dims.y - 1));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color(255, 255, 255, 100));

    center.setRadius(5);
    center.setOrigin(5, 5);
    center.setFillColor(sf::Color::Red);
    center.setPosition(shape.getPosition().x, shape.getPosition().y);

    setupWall();
  }

  template <typename T>
  void setupNeighbors(sf::Vector2i colsRows, T& grid) {
    int cols = colsRows.x;
    int rows = colsRows.y;

    // Top
    if (j > 0) {
      neighbors.push_back(&grid.getCell(i, j - 1));
    }

    // Right
    if (i < cols - 1) {
      neighbors.push_back(&grid.getCell(i + 1, j));
    }

    // Bottom
    if (j < rows - 1) {
      neighbors.push_back(&grid.getCell(i, j + 1));
    }

    // Left
    if (i > 0) {
      neighbors.push_back(&grid.getCell(i - 1, j));
    }

    // Top Right
    if (j > 0 && i < cols - 1) {
      neighbors.push_back(&grid.getCell(i + 1, j - 1));
    }

    // Bottom Right
    if (j < rows - 1 && i < cols - 1) {
      neighbors.push_back(&grid.getCell(i + 1, j + 1));
    }

    // Top Left
    if (j > 0 && i > 0) {
      neighbors.push_back(&grid.getCell(i - 1, j - 1));
    }

    // Bottom Left
    if (j < rows - 1 && i > 0) {
      neighbors.push_back(&grid.getCell(i - 1, j + 1));
    }
  }

  void setPrevious(Cell* prev) { previous = prev; }

  void setAsStartingCell() {
    startingCell = true;
    wall = false;
    shape.setFillColor(sf::Color::Transparent);
  }

  void setAsEndingCell() {
    endingCell = true;
    wall = false;
    shape.setFillColor(sf::Color::Transparent);
  }

  void setupWall() {
    float randomFloat = Utility::genRandomFloat(0, 1.0f);
    if (randomFloat < 0.25f) {
      shape.setFillColor(sf::Color(0, 0, 0, 100));
      wall = true;
    }
  }

  void draw(sf::RenderWindow& window) {
    window.draw(shape);
    // window.draw(center);
  }
  void draw(sf::RenderWindow& window, sf::Color color) {
    shape.setFillColor(color);
    window.draw(shape);
    // window.draw(center);
  }
};

