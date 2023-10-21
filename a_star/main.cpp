#include <SFML/Graphics.hpp>
#include <iostream>

#include "EventsUtility.hpp"
#include "Grid.hpp"
#include "utility.hpp"

sf::Vector2f windowSize = sf::Vector2f(1000.0f, 800.0f);

int main() {
  Grid grid = Grid(windowSize);

  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML");
  window.setFramerateLimit(EventsUtility::FRAMERATE);

  // Main Loop
  while (window.isOpen()) {
    EventsUtility::handleCloseEvent(window);
    window.clear(EventsUtility::bgColor);
    grid.draw(window);
    window.display();
  }

  return 0;
}
