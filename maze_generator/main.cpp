#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "Cell.hpp"

sf::Vector2f windowSize = sf::Vector2f(1000.0f, 1000.0f);
sf::Color bgColor = sf::Color(51, 50, 50);
const int FRAMERATE = 30;
const int CELL_WIDTH = 40;

const int cols = floor(windowSize.x / CELL_WIDTH);
const int rows = floor(windowSize.y / CELL_WIDTH);
const int gridSize = cols * rows;

void removeWalls(Cell* a, Cell* b) {
  int x = a->i - b->i;

  if (x == 1) {
    a->walls[3] = false;
    b->walls[1] = false;
  }
  if (x == -1) {
    a->walls[1] = false;
    b->walls[3] = false;
  }

  int y = a->j - b->j;

  if (y == 1) {
    a->walls[0] = false;
    b->walls[2] = false;
  }
  if (y == -1) {
    a->walls[2] = false;
    b->walls[0] = false;
  }
}

int main() {
  std::vector<std::unique_ptr<Cell> > grid;
  std::vector<Cell*> stack;

  for (int j = 0; j < rows; ++j) {
    // std::cout << j << std::endl;

    for (int i = 0; i < cols; ++i) {
      // std::cout << j << std::endl;
      grid.push_back(std::make_unique<Cell>(i, j, cols, rows));
    }
  }
  Cell* currentCell = grid[0].get();

  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML");
  window.setFramerateLimit(FRAMERATE);

  // Main Loop
  while (window.isOpen()) {
    sf::Event event;

    if (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(bgColor);

    for (size_t i = 0; i < grid.size(); i++) {
      grid[i]->draw(window);
    }

    currentCell->isVisited = true;
    currentCell->highlight(window);

    Cell* next = currentCell->checkNeighbors(grid);
    if (next != nullptr) {
      stack.push_back(next);
      next->isVisited = true;
      removeWalls(currentCell, next);
      currentCell = next;
    } else {
      if (!stack.empty()) {
        Cell* lastCell = stack.back();
        stack.pop_back();
        currentCell = lastCell;
      }
    }

    window.display();
  }

  return 0;
}
