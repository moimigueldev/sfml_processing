#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.hpp"
#include "MazeGenerator.hpp"

class Game {
 private:
 public:
  std::vector<std::vector<Cell> > grid;
  Game() {}

  void draw(sf::RenderWindow& window) {}
};

