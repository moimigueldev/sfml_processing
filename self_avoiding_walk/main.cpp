#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Path.hpp"
#include "Cell.hpp"
#include <cmath>

sf::Vector2f windowSize = sf::Vector2f(1000.0f, 800.0f);
sf::Color bgColor = sf::Color(68, 70, 83);
const int FRAMERATE = 10;
const int PATH_SIZE = 20;
const float COLS = floor(windowSize.x / PATH_SIZE);
const float ROWS = floor(windowSize.y / PATH_SIZE);
int count = 0;
int n_denied = 64;

int main() {
  std::vector<std::unique_ptr<Cell> > grid;
  std::vector<Cell*> stack;
  std::vector<sf::Vector2f> visitedCords;
  sf::VertexArray lines(sf::LineStrip);
  lines.append(sf::Vertex(sf::Vector2f(0, 0), sf::Color::Red));

  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML");
  window.setFramerateLimit(200);

  for (int j = 0; j < ROWS; j++) {
    for (int i = 0; i < COLS; i++) {
      grid.push_back(std::make_unique<Cell>(sf::Vector2f(i, j), PATH_SIZE, ROWS, COLS));
    }
  }

  Cell* current = grid[0].get();

  // Main Loop
  while(window.isOpen()) {
    sf::Event event;

    if(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(bgColor);

    for (int i = 0; i < grid.size(); i++) {
      grid[i]->draw(window);
    }

    Cell* next = current->move(grid, lines);

    if(count <= n_denied) {

    if(next != nullptr) {
      stack.push_back(current); // push the current cell before updating it
      current = next;
      count = 0;
    } else {
      if(!stack.empty()) {
        // backtrack: remove the current position from the lines vertex
        if (lines.getVertexCount() > 0) {
          lines.resize(lines.getVertexCount() - 3);
          count++;
    cout << "denied" << endl;
        }


        current = stack.back();
        stack.pop_back();
      }
    }

    if (current) {
      lines.append(sf::Vertex(sf::Vector2f(current->position.x * PATH_SIZE, current->position.y * PATH_SIZE), sf::Color::Red));
    }

    } else {

  window.setFramerateLimit(FRAMERATE);
    }

    window.draw(lines);

    window.display();
    count++;
  }

  return 0;
}

