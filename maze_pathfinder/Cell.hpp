#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "utility.hpp"

class Cell {
 private:
  sf::Color wallColor = sf::Color(183, 183, 183);

 public:
  int i;
  int j;
  sf::Vector2f position;
  int cols;
  int rows;
  int w;
  Cell() = default;
  sf::VertexArray topLine = sf::VertexArray(sf::Lines, 2);
  sf::VertexArray rightLine = sf::VertexArray(sf::Lines, 2);
  sf::VertexArray bottomLine = sf::VertexArray(sf::Lines, 2);
  sf::VertexArray leftLine = sf::VertexArray(sf::Lines, 2);
  Cell(int i_pos, int j_pos, sf::Vector2f dims, int& width) {
    i = i_pos;
    j = j_pos;
    w = width;

    cols = dims.x;
    rows = dims.y;
    position = sf::Vector2f(i * w, j * w);
    setupWalls();
  }

  void draw(sf::RenderWindow& window) {
    window.draw(topLine);
    window.draw(rightLine);
    window.draw(bottomLine);
    window.draw(leftLine);
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
};

