#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.hpp"
#include "Grid.hpp"
#include "utility.hpp"

class Game {
 private:
 public:
  Grid grid;
  Game() {}

  void draw(sf::RenderWindow& window) { grid.draw(window); }
};
