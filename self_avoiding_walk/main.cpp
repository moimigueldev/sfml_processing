#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Path.hpp"
#include "Cell.hpp"
#include <cmath>

sf::Vector2f windowSize = sf::Vector2f(1000.0f, 800.0f);
sf::Color bgColor = sf::Color(68, 70, 83);
const int FRAMERATE = 60;
const int PATH_SIZE = 50;
const float COLS = floor(windowSize.x / PATH_SIZE);
const float ROWS = floor(windowSize.y / PATH_SIZE);



int main() {


  std::vector<std::unique_ptr<Cell> > grid;
  std::vector<sf::Vector2f> visitedCords;

  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML");
  window.setFramerateLimit(FRAMERATE);


  for (int j = 0; j < ROWS; j++) {
    for (int i = 0; i < COLS; i++) {
      grid.push_back(std::make_unique<Cell>(sf::Vector2f(i, j), PATH_SIZE));
    }
  }

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

    window.display();

  }

  return 0;
}
